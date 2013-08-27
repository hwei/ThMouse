ThMouse
=======

Introduction
------------

THMouse is a third-party software that enables mouse control in Touhou danmaku game series, allowing player character to move towards wherever the cursor points (within the danmaku border).

Compatibility
-------------

* TH10.exe ~ Mountain of Faith 
* TH11.exe ~ Subterranean Animism 
* TH12.exe ~ Undefined Fantastic Object 
* TH125.exe ~ Shoot the Bullet DS
* TH128.exe ~ Fairy Wars 
* TH13.exe ~ Ten Desires (ver1.00c)
* TH14.exe ~ Double Dealing Character (ver1.00b 1280*960 resolution)

FAQ
---

### How to compile?
1. Install Windows SDK (or Vitual Studio), DirectX SDK, CMake (and add cmake to PATH).
2. Open Windows SDK shell (or cmd), and go to ThMouse source folder, for example C:\ThMouse, type:
    ```
    mkdir build
    cd build
    cmake ..
    ```
3. Use NMake (or Vitual Studio) to build the project ThMouse. 
4. You can get compile result at `C:\ThMouse\build\bin` .

### How to install?

Just put all files (cursor.png, games, ThDxHook.dll, ThMouse.exe, ThMouse.ini) in the same folder.

### How to enable ThMouse?

1. Run ThMouse.exe before entering the game.
2. Enable the option to select resolutions when initiating the game. (Or ThMouse will NOT work.)
3. Select the lowest resolution or fullscreen. (All other resolutions will cause displaced mouse cursors.)
4. If the game is supported, a crosshair will show upon entering the game.

### How to control?

* The character will move towards where the cursor points. Please note that it will NOT move immidiately with the cursor, because ThMouse can not change moving speed.
* You still have to use left hand to control low speed and fire buttons.
* Left click can initiate bomb.
* Right click can turn off mouse control temporally.

### How to close it?

1. Exit game first.
2. Double-click the ThMouse icon on the taskbar and press quit button.

Additional Instructions
-----------------------

### Bomb for TH11

In order to bomb in TH11 (Subterranean Animism), you may need to modify ThMouse.ini:

1. Run TH11.exe, go to OPTIONS, then KEY CONFIG.
2. Find the number xx that corresponds to the button "SPECIAL".
3. Exit the game and open up ThMouse.ini.
4. change the number after "LeftButton = " to the number you find through step 1-2.

### Cursor sprite

The crosshair/cursor sprite may be changed:

1. Find your preferred crosshair in .png format and place it into the same folder as ThMouse.exe.
2. Open up ThMouse.ini.
3. Change the file name after "CursorTexture = " to the preferred crosshair file's name. (Don't forget the file extension name ".png".)

### "games" file

You can extend ThMouse to support more TouHou danmaku games (localized or moded version, or just another new version) by modifying "games" file.
Open the file with any text editor and try yourself.