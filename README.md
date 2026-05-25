A simple banking application written in C with sqlite3 for database and GTK-3 for GUI.

#### [still in progress]

#### Building

* Dependencies
    * GTK3
    * sqlite3


* With Ninja
```
    cmake -B build -G Ninja
    ninja -C build
    ./build/final

```

* With Make

```
    cmake -B build -G "Unix Makefiles"
    cmake --build
    ./build/final

```

* Application

    ![Main Page](images/main-page.png)

    ![Client Page](images/client-page.png)