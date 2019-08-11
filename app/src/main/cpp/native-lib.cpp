#include <jni.h>
#include <string>
#include <__locale>
#include<android/log.h>
#define TAG "FirdaStudy" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_frida_1study_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello JNI";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_frida_1study_MainActivity_n_1fun(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    // 将输入直接输出
    std::string ret = str;
    char buf[256];
    env->GetStringUTFRegion(str_,0,env->GetStringLength(str_),buf);
    LOGD("n_1fun: 输入的值再次输出,输入的值->%s",buf);
    env->ReleaseStringUTFChars(str_, str);
    return env->NewStringUTF(ret.c_str());
}

//
static const char* class_Study = "com/example/frida_study/Study";

static jstring fun1(JNIEnv* env,jobject obj){
    std::string s = "Welcome!";
    LOGD("native_fun ret String Welcome!");
    return env->NewStringUTF(s.c_str());
}

static jstring fun2(JNIEnv* env,jobject obj,jstring str){
    char buf[256];
    env->GetStringUTFRegion(str,0,env->GetStringLength(str),buf);
    LOGD("native_str: 输入的值->%s",buf);

    const char* ptr_c=env->GetStringUTFChars(str,NULL);
    LOGD("返回const char* 类型：%s",ptr_c);
    const jchar *ret=env->GetStringChars(str, NULL);
    LOGD("返回const jchar* 类型");
    env->ReleaseStringChars(str,ret);

    jstring s=env->NewStringUTF(buf);
    return env->NewString(ret,env->GetStringLength(str));
}

jint test(int a,int b){
    return a*b;
}

static void setage(JNIEnv* env,jobject obj, jint n){
    jint base = 200;
    jint res = test(base,n);
    LOGD("setage调用内部函数test");
    LOGD("setage输入的参数为%d",n);
    LOGD("setage返回值为%d",res);
    jclass clazz=env->GetObjectClass(obj);
    jfieldID id=env->GetFieldID(clazz,"age","I");
    LOGD("setage获取到的age值为%d",id);
    env->SetIntField(obj,id,res);
}


static JNINativeMethod methods[] = {
        {"native_fun","()Ljava/lang/String;",(void*)fun1},
        {"native_str","(Ljava/lang/String;)Ljava/lang/String;",(void*)fun2},
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