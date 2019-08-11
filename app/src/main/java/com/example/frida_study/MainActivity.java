package com.example.frida_study;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    final static String TAG = "FirdaStudy";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        Button bt = findViewById(R.id.button);
        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Study study = new Study("NONO",100);
                study.show();

                Log.d(TAG, "---------------------Naitve分割线----------------------");
                n_fun("YES");
                study.native_fun();
                study.native_str("OKOK");
                study.setage(10);

            }
        });

    }

    // 直接注册 方法
    public native String stringFromJNI();
    public native String n_fun(String str);
}
