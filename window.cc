#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  cout << "Diplay is opened" << endl;
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[16][10] = {"white",  "black", "khaki", "lavender", "olive", "honeydew", "linen", "red", "green",
		"blue",   "cyan",  "yellow",   "magenta",
		"orange", "brown", "darkgreen"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 14; ++i) {
    XParseColor(d,cmap,color_vals[i],&xcolour);
    XAllocColor(d,cmap,&xcolour);
    colours[i]=xcolour.pixel;
  }
  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);



  usleep(1000);
}

Xwindow::~Xwindow() {
	std::cout << "start of xwindow destructor" << std::endl;
  XFreeGC(d, gc);
  std::cout << "middle of xwindow destructor" << std::endl;
//XCloseDisplay(d);
  std::cout << "end of xwindow destructor" << std::endl;
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  std::cout << "fill rect1";
  XSetForeground(d, gc, colours[colour]);
  std::cout << "fill rect2";
  XFillRectangle(d, w, gc, x, y, width, height);
  std::cout << "fill rect3";
  XSetForeground(d, gc, colours[Black]);
  std::cout << "fill rect4";
}

#include <iostream>

void Xwindow::drawStringFont(int x, int y, string msg, string font, int colour) {
  XFontStruct * f = XLoadQueryFont(d, font.c_str());
  
	if ( f == nullptr ){
		f = XLoadQueryFont(d, "6x13");
	}

	// printMessage(x, y, msg, colour, *f);
	delete f;
}

void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  int width = 5;
  int height = 5;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

	drawStringFont(x, y, msg, name.str(), colour);
}

void Xwindow::drawString(int x, int y, string msg, int fontSize) {
  std::cout << "check0" << std::endl;
  //std::cout << XLoadQueryFont(d, "-adobe-helvetica-medium-r-normal--8-80-75-75-p-46-iso10646-1");
  //std::cout << "check0";
  //auto font = XLoadQueryFont(d, "*-helvetica-*-12-*");
  //std::cout << "check1" << std::endl;
  //XSetFont(d, DefaultGC(d, s), font->fid);
  //std::cout << "check2" << std::endl;
  XDrawString(d,w,gc,x,y,msg.c_str(), msg.length());
  //XDrawString(d, w, DefaultGC(d, s), x, y + font->ascent, msg.c_str(), msg.length());
   std::cout << "check3" << std::endl;
}

