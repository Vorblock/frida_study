#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_frida_1study_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_frida_1study_MainActivity_n_1fun(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    // TODO

    env->ReleaseStringUTFChars(str_, str);

    return env->NewStringUTF(returnValue);
}


//
static const char* class_Study = "com/example/frida_study/Study";

static jstring native_fun(JNIEnv* env,jobject){

}

static jstring str_fun(JNIEnv* env,jobject ,jstring str){

}

static void setage(JNIEnv* env,jobject, int n){


}
static JNINativeMethod methods[] = {
        {"native_fun","()Ljava/lang/String;",(void*)native_fun},
        {"str_fun","(Ljava/lang/String;)Ljava/lang/String;",(void*)str_fun},
        {"setage","(I)V",(void*)setage}
};



static int jniMethods(JNIEnv* env, const char* classname, const JNINativeMethod* gMethods,
        int numMethods){
    jclass clazz;

    clazz = (env)->FindClass(classname);
    if(clazz == NULL ) return -1;



    int res = 0;
    if((env)->RegisterNatives(clazz,methods,numMethods) <0 ){
        return -1;
    }
    (env)->DeleteLocalRef(clazz);
    return res;

}

//重写JNI_OnLoad
jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint res = -1;
    if(vm->GetEnv((void**) &env,JNI_VERSION_1_6) != JNI_OK){
        return res;
    }
    jniMethods(env,class_Study,methods,sizeof(methods)/sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}