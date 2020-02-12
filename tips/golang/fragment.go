package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

// defer 是后进先出。 协程遇到panic时，遍历本协程的defer链表，并执行defer。
//在执行defer过程中，遇到recover则停止panic，返回recover处继续往下执行。
//如果没有遇到recover，遍历完本协程的defer链表后，向stderr抛出panic信息。
//从执行顺序上来看，实际上是按照先进后出的顺序执行defer
func DeferCall() {
	defer func() { fmt.Println("打印前") }()
	defer func() { fmt.Println("打印中") }()
	defer func() { fmt.Println("打印后") }()

	panic("触发异常")
}

// go执行的随机性和闭包
func RandomWg() {
	runtime.GOMAXPROCS(1)
	wg := sync.WaitGroup{}
	wg.Add(20)
	for i := 0; i < 10; i++ {
		go func() {
			fmt.Println("A: ", i)
			wg.Done()
		}()
	}
	for i := 0; i < 10; i++ {
		go func(i int) {
			fmt.Println("B: ", i)
			wg.Done()
		}(i)
	}
	wg.Wait()
}

// 用信道实现主程等待协程2s,如果超过2s,主程直接结束(不用sleep)
func Sleep2s() {
	start := time.Now()
	wait := make(chan struct{}, 2)

	go func() {
		fmt.Println("do something")
		time.Sleep(1 * time.Second)
		wait <- struct{}{}
	}()

	fmt.Println("this is the main program")
	for {
		select {
		case _ = <-wait:
			fmt.Println("received message")
			goto OVER
		case <-time.After(2 * time.Second):
			fmt.Println("after 2 seconds")
			goto OVER
		}
	}

OVER:
	fmt.Println(time.Since(start))
}

func main() {
}
