// generated by Fast Light User Interface Designer (fluid) version 1.0300

#ifndef ConfigUI_h
#define ConfigUI_h
#include <FL/Fl.H>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <FL/Fl_File_Chooser.H>
#include "../globals.h"
#include "../Misc/Util.h"
#include "../Misc/Dump.h"
extern Dump dump;
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>

class ConfigUI {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *configwindow;
private:
  void cb_configwindow_i(Fl_Double_Window*, void*);
  static void cb_configwindow(Fl_Double_Window*, void*);
  void cb__i(Fl_Choice*, void*);
  static void cb_(Fl_Choice*, void*);
  static Fl_Menu_Item menu_[];
public:
  Fl_Int_Input *samplerateinput;
private:
  void cb_samplerateinput_i(Fl_Int_Input*, void*);
  static void cb_samplerateinput(Fl_Int_Input*, void*);
  void cb_Buffer_i(Fl_Int_Input*, void*);
  static void cb_Buffer(Fl_Int_Input*, void*);
  void cb_Swap_i(Fl_Check_Button*, void*);
  static void cb_Swap(Fl_Check_Button*, void*);
  void cb_OscilSize_i(Fl_Choice*, void*);
  static void cb_OscilSize(Fl_Choice*, void*);
  static Fl_Menu_Item menu_OscilSize[];
  void cb_Dump_i(Fl_File_Input*, void*);
  static void cb_Dump(Fl_File_Input*, void*);
  void cb_Dump1_i(Fl_Check_Button*, void*);
  static void cb_Dump1(Fl_Check_Button*, void*);
  void cb_Append_i(Fl_Check_Button*, void*);
  static void cb_Append(Fl_Check_Button*, void*);
  void cb_XML_i(Fl_Counter*, void*);
  static void cb_XML(Fl_Counter*, void*);
  void cb_PADsynth_i(Fl_Choice*, void*);
  static void cb_PADsynth(Fl_Choice*, void*);
  static Fl_Menu_Item menu_PADsynth[];
  void cb_Virtual_i(Fl_Choice*, void*);
  static void cb_Virtual(Fl_Choice*, void*);
  static Fl_Menu_Item menu_Virtual[];
  void cb_Ignore_i(Fl_Check_Button*, void*);
  static void cb_Ignore(Fl_Check_Button*, void*);
public:
  Fl_Browser *rootsbrowse;
private:
  void cb_rootsbrowse_i(Fl_Browser*, void*);
  static void cb_rootsbrowse(Fl_Browser*, void*);
  void cb_Add_i(Fl_Button*, void*);
  static void cb_Add(Fl_Button*, void*);
public:
  Fl_Button *removerootdirbutton;
private:
  void cb_removerootdirbutton_i(Fl_Button*, void*);
  static void cb_removerootdirbutton(Fl_Button*, void*);
public:
  Fl_Button *makedefaultrootdirbutton;
private:
  void cb_makedefaultrootdirbutton_i(Fl_Button*, void*);
  static void cb_makedefaultrootdirbutton(Fl_Button*, void*);
public:
  Fl_Browser *presetbrowse;
private:
  void cb_presetbrowse_i(Fl_Browser*, void*);
  static void cb_presetbrowse(Fl_Browser*, void*);
  void cb_Add1_i(Fl_Button*, void*);
  static void cb_Add1(Fl_Button*, void*);
public:
  Fl_Button *removepresetbutton;
private:
  void cb_removepresetbutton_i(Fl_Button*, void*);
  static void cb_removepresetbutton(Fl_Button*, void*);
public:
  Fl_Button *makedefaultpresetbutton;
private:
  void cb_makedefaultpresetbutton_i(Fl_Button*, void*);
  static void cb_makedefaultpresetbutton(Fl_Button*, void*);
  void cb_Close_i(Fl_Button*, void*);
  static void cb_Close(Fl_Button*, void*);
public:
  ConfigUI();
  void activatebutton_rootdir(bool active);
  void activatebutton_presetdir(bool active);
  void readbankcfg();
  void writebankcfg();
  void readpresetcfg();
  void writepresetcfg();
  int getsamplerateorder();
  void setsamplerateinput();
  void show();
};
#endif
