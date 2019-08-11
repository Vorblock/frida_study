package com.example.frida_study;

import android.util.Log;

public class Study extends Book{

    private static final String TAG = "FirdaStudy";
    public static String hook = "Hello,frida!";
    private int age;
    //
    //继承构造函数
    public Study(String name) {
        super(name);
    }
    //构造函数
    public Study(String name, int age) {
        super(name);
        this.age = age;
    }

    //无返回函数
    public void void_fun(String str){
        Log.d(TAG, "void_fun: "+str);
    }
    //  int 1个返回参数
    public int int_fun(int a){
        Log.d(TAG, "str_fun: "+a*a);
        return a*a;
    }
    // 2个返回参数
    public String str_fun(String str1,String str2){
        Log.d(TAG, "int_fun->str1: "+str1);
        Log.d(TAG, "int_fun->str2: "+str2);
        return str1+" and "+ str2;
    }

    byte[] bytes = hook.getBytes();

    public byte[] byte_fun(byte[] bytes){
        for (int i = 0; i < bytes.length; i++) {
            Log.d(TAG, "byte_fun->"+i+": "+bytes[i]);
        }
        StringBuffer sb = new StringBuffer(bytes.toString());
        return sb.reverse().toString().getBytes();
    }
    //内部类
    class inner_class{
        private String data;
        public inner_class(String str){
            Log.d(TAG, "inner_class: "+str);
        }
        public String inner_class_fun(String str){
            Log.d(TAG, "inner_class_fun: "+str);
            this.data = str;

            return data;
        }

    }


    public void show(){
        void_fun(hook);
        Log.d(TAG, "int_fun_ret: "+int_fun(10));
        Log.d(TAG, "str_fun_ret: "+str_fun("you","me"));
        Log.d(TAG, "byte_fun_ret: "+byte_fun(bytes).toString());
        inner_class cz = new inner_class("are you ok?");
        Log.d(TAG, "inner_fun_ret: "+cz.inner_class_fun("I'm fine!"));
    }

    //native 方法 动态注册方法
    public native String native_fun();
    public native String native_str(String str);
    public native void setage(int a);

}
