
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <ltdl.h>
#include <stdio.h>
#include <unistd.h>
#include "shape.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::list;
using std::vector;

// size of buffer for reading in directory entries
const unsigned BUF_SIZE = 1024;

int main(int argc, char *argv[])
{
  FILE *dl;   // handle to read directory
  // command string to get dynamic lib names
  const char *command_str = "find . -name \\*.so";

  char in_buf[BUF_SIZE]; // input buffer for lib names
  list<lt_dlhandle> dl_list; // list to hold handles for dynamic libs
  list<lt_dlhandle>::iterator itr;
  vector<string> shape_names;  // vector of shape types used to build menu
  list<shape *> shape_list;  // list of shape objects we create
  list<shape *>::iterator sitr;
  factory_iterator fitr;
  // get the names of all the dynamic libs (.so files) in the current dir
  dl = popen(command_str, "r");
  if (!dl) {
    perror("popen");
    return !0;
  }
  lt_dlhandle dlib;
  char name[BUF_SIZE+2];
  if (lt_dlinit()) {
    cerr << lt_dlerror() << endl;
    return !0;
  }
  while (fgets(in_buf, BUF_SIZE, dl)) {
    // trim off the whitespace
    char *ws = strpbrk(in_buf, " \t\n");
    if (ws) *ws = '\0';
    // append ./ to the front of the lib name
    sprintf(name, "./%s", in_buf);
    dlib = lt_dlopen(name);
    if (dlib == NULL) {
      cerr << lt_dlerror() << endl;
      return !0;
    }
    else {
      std::cout << "loading " << name << std::endl;
    }
    // There is no valid cast between pointer to function and pointer to object
    // See http://www.trilithium.com/johan/2004/12/problem-with-dlsym/
    typedef void *(funObj)();
    funObj *registerShape = reinterpret_cast<funObj*>(lt_dlsym(dlib, "registerShape"));
    const char *error;
    if ( (error = lt_dlerror()) ) {
      cerr << error << endl;
      return !0;
    }
    // register shape in factory
    registerShape();

    // add the handle to our list
    dl_list.insert(dl_list.end(), dlib);
  }
  // variable to access the factory
  shapeFactory factory = shapeFactory::instance();
  // create an array of the shape names
  for (fitr=factory.begin(); fitr!=factory.end(); ++fitr) {
    shape_names.insert(shape_names.end(), fitr->first);
  }
  // create a menu of possible shapes to create and let the user make some
  while (true) {
    int i = 1;
    int choice;
    for (fitr=factory.begin(); fitr!=factory.end(); ++fitr) {
      cout << i << " - Create " << fitr->first << endl;
      ++i;
    }
    cout << i << " - Draw created shapes\n";
    ++i;
    cout << i << " - Exit\n";
    cout << "> ";
    cin >> choice;
    if (choice == i) {
      // destroy any shapes we created
      for (sitr=shape_list.begin(); sitr!=shape_list.end(); ++sitr) {
        std::cout << "deleting shape " << std::hex << *sitr << std::endl;
        delete *sitr;
      }
      // close all the dynamic libs we opened
      std::cout << "closing dynamic libraries" << std::endl;
      for (itr=dl_list.begin(); itr!=dl_list.end(); ++itr) {
        lt_dlclose(*itr);
      }
      return !0;
    }
    if (choice == i - 1) {
      // draw the shapes
      for (sitr=shape_list.begin(); sitr!=shape_list.end(); ++sitr) {
        (*sitr)->draw();
      }
    }
    if (choice > 0 && choice < i - 1) {
      // add the appropriate shape to the shape list
      shape_list.insert(shape_list.end(),factory.create(shape_names[choice-1]));
    }
  }
  return 0;
}


