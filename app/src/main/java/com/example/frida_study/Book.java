package com.example.frida_study;

import android.util.Log;

public class Book {
    private String name;

    public Book(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    public Book(){
        Log.d("Book", "my book");
    }
    //隐藏函数
    private String secret(){
        Log.d("Book", "HOOK ME!");
        return "HOOK ME!";
    }
}
