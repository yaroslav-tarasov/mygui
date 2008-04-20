/*!
	@file
	@author		Albert Semenov
	@date		12/2007
	@module
*/
#include "DemoKeeper.h"
#include <fstream>

DemoKeeper::DemoKeeper() :
	mGUI(0),
	mWidth(1), mHeight(1)
{
}

MyGUI::WidgetPtr but = 0;

MyGUI::ButtonPtr button = 0;

MyGUI::SheetPtr sheet = null;
MyGUI::ProgressPtr progress = null;

void DemoKeeper::move(int _left, int _top)
{
	if (but != 0) but->setPosition(_left+2, _top+2);

	//if (button != 0) MyGUI::MYGUI_OUT(button->getTextSize());
	if (progress) progress->setProgressPosition(_left);

}

MyGUI::PopupMenuPtr menu = null;

void DemoKeeper::pressed(int _left, int _top, bool _leftbutton)
{
}

void DemoKeeper::released(int _left, int _top, bool _leftbutton)
{
	if (null != sheet) {
		//MyGUI::WidgetManager::getInstance().findWidget<MyGUI::Tab>("main_tab")->removeSheet(sheet);
		sheet = null;
	}

	/*char * names [3] = {"core.png", "foto.png", "1.jpg"};
	static size_t num = 0;
	num++;
	if (num > 2) num = 0;

	_sender->_setTextureName(names[num]);*/
	if ((menu) && (!_leftbutton)) menu->showPopupMenu(MyGUI::IntPoint(_left, _top));
	
}

void requestCreateItem(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _parent, MyGUI::WidgetPtr & _item)
{
	if (_parent) _item = _parent->createWidget<MyGUI::Widget>("ButtonSmall", MyGUI::IntCoord(), MyGUI::ALIGN_DEFAULT);
	else _item = MyGUI::Gui::getInstance().createWidget<MyGUI::Widget>("ButtonSmall", MyGUI::IntCoord(), MyGUI::ALIGN_DEFAULT, "DragAndDrop");
}

void requestCoordItem(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _client, MyGUI::IntCoord & _coord, bool _drop)
{
	if (_drop) {
		_coord.set(-10, -10, 100, 70);
	}
	else {
		_coord.set(0, 0, 80, 50);
	}
}

void requestUpdateItem(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _item, const MyGUI::ItemInfo& _data)
{
	if (_data.select) _item->setState(_data.active ? "select" : "pressed");
	else _item->setState(_data.active ? "active" : "normal");

	if (_data.drag) {
		MyGUI::IntSize size = _item->getSize();
		if (_data.drag_result) _item->setAlpha(0.6);
		else _item->setAlpha(0.2);
	}
	else _item->setAlpha(ALPHA_MAX);

	if (_data.drag_accept) _item->setCaption(MyGUI::utility::toString(_data.index, "_accept"));
	else if (_data.drag_refuse) _item->setCaption(MyGUI::utility::toString(_data.index, "_refuse"));
	else if (_data.drag) _item->setCaption(MyGUI::utility::toString(_data.index, "_drag"));
	else _item->setCaption(MyGUI::utility::toString(_data.index));

	if (false == _data.only_state) {
		if ( ! _data.drag) {
			_item->setCaption(MyGUI::utility::toString(_data.index));
		}
	}
}

void requestDropItem(MyGUI::WidgetPtr _sender, const MyGUI::ItemDropInfo & _info, bool & _result)
{
	_result  = (_info.index_reseiver % 2) == 0;
}

void eventDropAccept(MyGUI::WidgetPtr _sender, MyGUI::ItemDropInfo _info)
{
	MyGUI::MYGUI_OUT("drop");
}

void DemoKeeper::start(MyGUI::Gui * _gui, size_t _width, size_t _height)
{
    mGUI = _gui;
    mWidth = _width;
    mHeight = _height;

	/*menu = mGUI->createWidget<MyGUI::PopupMenu>("PopupMenu", MyGUI::IntCoord(), MyGUI::ALIGN_BOTTOM, "Main");
	menu->addItem("test 1");
=======
	MyGUI::WidgetPtr button = mGUI->createWidgetT("StrangeButton", "Button", MyGUI::IntCoord(100, 100, 100, 100), MyGUI::ALIGN_BOTTOM, "Main");
	button->setCaption("StrangeButton");
	/*menu->addItem("test 1");
>>>>>>> .r638
	menu->addItem("test 2");
	menu->addItem("test 3");
	menu->addItem("test 4");*/
	//menu->showPopupMenu(MyGUI::IntPoint(10, 10));

	//MyGUI::PointerManager::getInstance().setPointer("hand", null);

	/*MyGUI::FooBar* bar = mGUI->createWidget<MyGUI::FooBar>("FooBar", MyGUI::IntCoord(100, 100, 500, 50), MyGUI::ALIGN_BOTTOM, "Main");
	bar->setLayout(MyGUI::FooBar::FBL_SNAP_BOTTOM);
	//MyGUI::LayerManager::getInstance().attachToLayerKeeper("Main", bar);
	bar->show();
	bar->setWidth(64);
	//for (int i = 0; i < 10; i++)
		//bar->addItem(Ogre::StringConverter::toString(i), Ogre::StringConverter::toString(i) + ".png");
	bar->addItem(MyGUI::FooBarItemInfo("item1", "foobar.png", 0, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item2", "foobar.png", 1, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item3", "foobar.png", 2, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item4", "foobar.png", 3, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item5", "foobar.png", 4, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item6", "foobar.png", 5, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item7", "foobar.png", 6, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item8", "foobar.png", 7, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item9", "foobar.png", 8, MyGUI::FloatSize(64.f, 64.f)));
	bar->addItem(MyGUI::FooBarItemInfo("item10", "foobar.png", 9, MyGUI::FloatSize(64.f, 64.f)));*/
	

	//MyGUI::WidgetPtr widget1 = mGUI->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
	//MyGUI::WidgetPtr widget2 = widget1->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 260, 260), MyGUI::ALIGN_DEFAULT);
	//MyGUI::WidgetPtr widget3 = widget2->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 220, 220), MyGUI::ALIGN_DEFAULT);
	//MyGUI::WidgetPtr widget4 = widget3->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 180, 180), MyGUI::ALIGN_DEFAULT);
	//MyGUI::WidgetPtr widget5 = widget4->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 140, 140), MyGUI::ALIGN_DEFAULT);
	//MyGUI::WidgetPtr widget6 = widget5->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::ALIGN_DEFAULT);
	//MyGUI::WidgetPtr widget7 = widget6->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(20, 20, 60, 60), MyGUI::ALIGN_DEFAULT);

	//widget1->hide();
	//widget3->hide();
	//widget6->hide();

	//widget6->show();
	//widget1->show();

	/*MyGUI::VScrollPtr window = mGUI->createWidget<MyGUI::VScroll>("VScroll", MyGUI::IntCoord(10, 10, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
	window->hide();
	window->setScrollRange(100);
	window->setSize(100, 100);//*/

	MyGUI::WindowPtr win = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(30, 100, 440, 256), MyGUI::ALIGN_DEFAULT, "Overlapped");
	win->setCaption("drag and drop demo");
	MyGUI::ItemBoxPtr box = win->createWidget<MyGUI::ItemBox>("ItemBox", MyGUI::IntCoord(MyGUI::IntPoint(), win->getClientRect().size()), MyGUI::ALIGN_STRETCH);
	box->requestCreateItem = MyGUI::newDelegate(requestCreateItem);
	box->requestCoordItem = MyGUI::newDelegate(requestCoordItem);
	box->requestUpdateItem = MyGUI::newDelegate(requestUpdateItem);
	box->requestDropItem = MyGUI::newDelegate(requestDropItem);
	box->eventDropAccept = MyGUI::newDelegate(eventDropAccept);

	size_t num = 0;
	while (num < 100) {
		box->addItem();
		num ++;
	}

	win = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(550, 100, 440, 256), MyGUI::ALIGN_DEFAULT, "Overlapped");
	win->setCaption("drag and drop demo");
	box = win->createWidget<MyGUI::ItemBox>("ItemBox", MyGUI::IntCoord(MyGUI::IntPoint(), win->getClientRect().size()), MyGUI::ALIGN_STRETCH);
	box->requestCreateItem = MyGUI::newDelegate(requestCreateItem);
	box->requestCoordItem = MyGUI::newDelegate(requestCoordItem);
	box->requestUpdateItem = MyGUI::newDelegate(requestUpdateItem);
	box->requestDropItem = MyGUI::newDelegate(requestDropItem);
	box->eventDropAccept = MyGUI::newDelegate(eventDropAccept);

	num = 0;
	while (num < 100) {
		box->addItem();
		num ++;
	}

	/*MyGUI::RenderBoxPtr box = mGUI->createWidget<MyGUI::RenderBox>("RenderBox", MyGUI::IntCoord(400, 200, 300, 226), MyGUI::ALIGN_DEFAULT, "Overlapped");
	box->injectObject("Robot_helper_01.mesh");
	box->setAnimation("run_forward");
	box->setAutoRotation(true);*/

	//progress = win->createWidget<MyGUI::Progress>("Progress", MyGUI::IntCoord(10, 10, 206, 206), MyGUI::ALIGN_STRETCH);
	//progress->setProgressAutoTrack(true);
	//progress->setProgressRange(100);
	//progress->setProgressPosition(100);
	//progress->setProgressFillTrack(true);
	//edit->setCaption("#FFFFFFF");

	/*MyGUI::StaticTextPtr text = mGUI->createWidget<MyGUI::StaticText>("StaticText", MyGUI::IntCoord(300, 300, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
	text->setCaption("StaticText");*/

	/*MyGUI::StaticImagePtr image = (MyGUI::StaticImagePtr)MyGUI::WidgetManager::getInstance().createWidget("StaticImage", "StaticImage", MyGUI::IntCoord(100, 100, 100, 100), MyGUI::ALIGN_DEFAULT, null, "");

	image->_setTextureName("core.png");

	MyGUI::LayerManager::getInstance().attachToLayerKeeper("Main", image);*/



	/*MyGUI::TabPtr tab = mGUI->createWidget<MyGUI::Tab>("Tab", MyGUI::IntCoord(500, 400, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");

	MyGUI::SheetPtr sheet = tab->addSheet("Test 1");
	sheet->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(30, 30, 100, 30), MyGUI::ALIGN_DEFAULT);

	sheet = tab->addSheet("Test 2");
	sheet->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(40, 40, 100, 30), MyGUI::ALIGN_DEFAULT);*/


	//MyGUI::Message::createMessage("test", "message is very cool.", true, MyGUI::Message::Ok | MyGUI::Message::IconInfo);//*/

	/*MyGUI::RenderBoxPtr box = mGUI->createWidget<MyGUI::RenderBox>("StaticImage", MyGUI::IntCoord(300, 200, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
	box->injectObject("Robot_helper_01.mesh");
	box->setMouseRotation(true);
	//box->setAutoRotation(true);
	//box->setAlpha(0.3);
	box->setRotationAngle(Ogre::Degree(90));*/

	//MyGUI::TabPtr tab = mGUI->createWidget<MyGUI::Tab>("Tab", MyGUI::IntCoord(40, 40, 200, 200), MyGUI::ALIGN_DEFAULT, "Main");
	//tab->addSheet("test");

	/*MyGUI::VectorWidgetPtr wid = MyGUI::LayoutManager::getInstance().load("default.layout");

	MyGUI::WidgetManager & manager = MyGUI::WidgetManager::getInstance();
	manager.destroyWidget(manager.findWidget<MyGUI::Sheet>("sheet1"));*/


//	manager.findWidget<MyGUI::Sheet>("sheet1")->removeSheet();
	//manager.findWidget<MyGUI::Tab>("main_tab")->removeSheet(manager.findWidget<MyGUI::Sheet>("sheet1"));

	//sheet = MyGUI::castWidget<MyGUI::Sheet>(manager.findWidget<MyGUI::Sheet>("sheet1"));

	//MyGUI::PointerManager::getInstance().hide();

	//MyGUI::LayoutManager::getInstance().load("DIP.layout");
	//MyGUI::LayoutManager::getInstance().load("EditDemo.layout");
	//MyGUI::LayoutManager::getInstance().load("playlist.layout");

	//MyGUI::EditPtr edit = mGUI->createWidget<MyGUI::Edit>("EditStretch", MyGUI::IntCoord(40, 40, 200, 200), MyGUI::ALIGN_DEFAULT, "Main");
	//edit->setEditMultiLine(true);
	//edit->setCaption("ww");
	//MyGUI::InputManager::getInstance().setKeyFocusWidget(edit);//*/

	//MyGUI::WidgetManager::getInstance().destroyWidget(edit);//*/


	MyGUI::ComboBoxPtr combo = mGUI->createWidget<MyGUI::ComboBox>("ComboBox", MyGUI::IntCoord(40, 40, 200, 200), MyGUI::ALIGN_DEFAULT, "Main");
	

	for (size_t pos=0; pos<20; ++pos) {
		combo->addItem("askhaldjkfhglkadhfglkajd");

		//MyGUI::WindowPtr window = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(10+pos*15, 10+pos*15, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
		//window->setCaption("WindowCSX");
		//window->setAutoAlpha(true);

		/*MyGUI::ButtonPtr button = window->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(10, 10, 250, 250), MyGUI::ALIGN_DEFAULT);
		button->setCaption("Button 1");
		button->setTextAlign(MyGUI::ALIGN_DEFAULT);*/

	
		/*MyGUI::ListPtr list = window->createWidget<MyGUI::List>("List", MyGUI::IntCoord(MyGUI::IntPoint(), window->getClientRect().size()), MyGUI::ALIGN_STRETCH);
		list->addItem("#000000line 1");
		list->addItem("#0000FFline 2");
		list->addItem("#00FF00line 3");
		list->addItem("#00FFFFline 4");
		list->addItem("#FF0000line 5");
		list->addItem("#FF00FFline 6");
		list->addItem("#FFFF00line 7");
		list->addItem("#FFFFFFline 8");
		list->addItem("line 9");
		list->addItem("line 10");
		list->addItem("line 11");
		list->addItem("line 12");
		list->addItem("line 13");
		list->addItem("line 14");
		list->addItem("line 15");
		list->addItem("line 16");//*/

	}

	//wid->eventMouseButtonPressed = MyGUI::newDelegate(this, &DemoKeeper::test);

	/*wid = wid->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(10, 10, 200, 200), MyGUI::ALIGN_DEFAULT);
	wid->eventMouseButtonPressed = MyGUI::newDelegate(this, &DemoKeeper::test);

	wid = wid->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(10, 10, 160, 160), MyGUI::ALIGN_DEFAULT);
	wid->eventMouseButtonPressed = MyGUI::newDelegate(this, &DemoKeeper::test);

	wid = wid->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(10, 10, 120, 120), MyGUI::ALIGN_DEFAULT);
	wid->eventMouseButtonPressed = MyGUI::newDelegate(this, &DemoKeeper::test);

	wid = wid->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(10, 10, 50, 50), MyGUI::ALIGN_DEFAULT);
	wid->eventMouseButtonPressed = MyGUI::newDelegate(this, &DemoKeeper::test);*/

	 //but = mGUI->createWidget<MyGUI::Widget>("Button", MyGUI::IntCoord(0, 0, 10, 10), MyGUI::ALIGN_DEFAULT, "Pointer");

	 /*MyGUI::WidgetPtr wid = mGUI->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(300, 100, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");
     but = wid->createWidget<MyGUI::Widget>("ButtonSmall", MyGUI::IntCoord(10, 10, 100, 100), MyGUI::ALIGN_LEFT | MyGUI::ALIGN_BOTTOM );
	 but->setCaption("trkluukbhgjkgkjgkjgkjgkjhgkj\njktuvucuyrcuyrcyruyrvyryrcuyrcuyrucyr\nuyrcuyucycu765i7to8r7rc7ri7ri7riu6\nuy76r4cu76cu76c76cu7c876rc876tr");

	 MyGUI::WidgetPtr but2 = but->createWidget<MyGUI::Widget>("ButtonSmall", MyGUI::IntCoord(10, 10, 10, 10), MyGUI::ALIGN_LEFT | MyGUI::ALIGN_BOTTOM );
     but2->createWidget<MyGUI::Widget>("ButtonSmall", MyGUI::IntCoord(1, 1, 3, 3), MyGUI::ALIGN_LEFT | MyGUI::ALIGN_BOTTOM );

	 mGUI->createWidget<MyGUI::Window>("DefaultClient", MyGUI::IntCoord(500, 200, 300, 300), MyGUI::ALIGN_DEFAULT, "Overlapped");//*/
	 //but->setAlpha(0.7);
	 //but->setColour(Ogre::ColourValue::White);
     //but->createWidget<MyGUI::Widget>("DefaultClient", MyGUI::IntCoord(10, 10, 60, 26), MyGUI::ALIGN_LEFT | MyGUI::ALIGN_BOTTOM );

}

void DemoKeeper::end()
{
}
