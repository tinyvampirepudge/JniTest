#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_tinytongtong_jnitest_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++, 我是王蛋蛋的爸比";
    return env->NewStringUTF(hello.c_str());
}

/**
 * extern "C" ：主要作用就是为了能够正确实现C++代码调用其他C语言代码
 * JNIEXPORT，JNICALL ：告诉虚拟机，这是jni函数
 */
extern "C"
JNIEXPORT jstring JNICALL
native_getString(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++, 我也是王蛋蛋的爸比，不过我是动态注册的。";
    return env->NewStringUTF(hello.c_str());
}
/**
 * 对应java类的全路径名，.用/代替
 */
const char *classPathName = "com/tinytongtong/jnitest/MainActivity";

/**
 * JNINativeMethod 结构体的数组
 * 结构体参数1：对应java类总的native方法
 * 结构体参数2：对应java类总的native方法的描述信息，用javap -s xxxx.class 查看
 * 结构体参数3：c/c++ 种对应的方法名
 */
JNINativeMethod method[] = {{"getString", "()Ljava/lang/String;", (void *) native_getString}};

/**
 * 该函数定义在jni.h头文件中，System.loadLibrary()时会调用JNI_OnLoad()函数
 */
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //定义 JNIEnv 指针
    JNIEnv *env = NULL;
    //获取 JNIEnv
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    //获取对应的java类
    jclass clazz = env->FindClass(classPathName);
    //注册native方法
    env->RegisterNatives(clazz, method, 1);
    //返回Jni 的版本
    return JNI_VERSION_1_6;
}
