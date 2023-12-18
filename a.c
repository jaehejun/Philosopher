#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//typedef struct {
//    int* shared_resource;
//    pthread_mutex_t* mutex;
//} ThreadArg;

//void* thread_func(void* s_main)
//{
//    ThreadArg	*s_thread;

//	s_thread = (ThreadArg*)s_main;

//    // 공유 자원 접근 전 뮤텍스 락
//    pthread_mutex_lock(s_thread->mutex);

//    // 공유 자원 사용 코드
//	(*(s_thread->shared_resource))++;
//    printf("Shared Resource: %d\n", *(s_thread->shared_resource));

//    // 뮤텍스 언락
//    pthread_mutex_unlock(s_thread->mutex);

//	return NULL;
//}

//int main() {
//    // 공유 자원 동적 할당
//    int	*shared_resource;	// main thread의 stack에 포인터변수 생김

//	shared_resource = (int*)malloc(sizeof(int));	// heap영역에 동적으로 할당
//    *shared_resource = 0;

//    pthread_mutex_t mutex;  // stack에 위치하고 있음

//    // 뮤텍스 초기화
//    pthread_mutex_init(&mutex, NULL);

//    // 스레드 생성 및 실행
//    pthread_t thread1, thread2;

//    ThreadArg s_main;	// stack영역에 s_main 생성
//	s_main.shared_resource = shared_resource;	// stack영역의 shared_resource 포인터변수는 heap에 위치한 메모리를 가리키고 있음
//	s_main.mutex = &mutex;	// s_main.mutex는 stack에 위치한 메모리를(mutex) 가리키고 있음

//    pthread_create(&thread1, NULL, thread_func, &s_main);
//    pthread_create(&thread2, NULL, thread_func, &s_main);

//    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);

//    // 뮤텍스 제거
//    pthread_mutex_destroy(&mutex);

//    // 공유 자원 해제
//    free(shared_resource);

//    return 0;
//}
