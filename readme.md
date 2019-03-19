HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [x] **If you volunteer to give the presentation next week, check this.**

--------------------

1 how I design the observation
	1. I claim two function .One of them has a function call of another function ,so I can observe what will happen if there're fuction call inside a function which was called by another function.
	2. Setup some variable and do some calculation to see how does variables work in assembly code.
******************************************************************************************************************************
	void reset_handler(void)
	{
		int a =1;	// claim a variable to see what happen in assembly code  <observation 1>
		a++;		// change a variable's value to see what will happen     <observation 2>
		a--;
		int b =2;	
		int c =3;
		int d =4;
		int result;
		result= compute(a,b,c,d);	//call a function which also has another function inside it <observation 3>
	}

	int compute(int a,int b,int c,int d )	// how did the function call pass their augument <observation 4>
	{
		return a+b*sub(d,c);		// how did the result of function return <observation 5>
	}

	int sub(int d,int c)
	{
		return d-c;
	}

******************************************************************************************************************************

2 result 
	<observation 1> 
  	 e:	2301      	movs	r3, #1				int a =1;
  	10:	617b      	str	r3, [r7, #20]	// r7在這裡是sp
宣告一個local variable並賦值時，會先將要assign的數值存到reg，再存入stack裡面。

	<observation 2>
	  12:	697b      	ldr	r3, [r7, #20]			a++;
	  14:	3301      	adds	r3, #1
	  16:	617b      	str	r3, [r7, #20]
	  18:	697b      	ldr	r3, [r7, #20]			a--;
	  1a:	3b01      	subs	r3, #1
	  1c:	617b      	str	r3, [r7, #20]
當在一個function里對variables 做運算時，每個步驟得先將variable的值從stack memory load 到 register里。當register 運算完後得先存入 stack memory 才能進行下一步驟。

	<observation 3>
	32:	f000 f805 	bl	40 <compute>			compute(a,b,c,d);
		.
		.
		.
		.
	00000040 <compute>:
	  40:	b580      	push	{r7, lr}
	  42:	b084      	sub	sp, #16
	  44:	af00      	add	r7, sp, #0
		.
		.
		.
	52:	f000 f80b 	bl	6c <sub>			sub(d,c); // 在function裡面的function call

	<observation 4>
	  4e:	6838      	ldr	r0, [r7, #0]			sub(d,c);	
	  50:	6879      	ldr	r1, [r7, #4]
	  52:	f000 f80b 	bl	6c <sub>
		.
		.
		.
	0000006c <sub>:
		.
	  72:	6078      	str	r0, [r7, #4]			int sub(int d,int c){................}	
	  74:	6039      	str	r1, [r7, #0]
為了將function call 所需要的參數(augment)保留給所呼叫的function使用，在 jump 到被呼叫function前我們得要先將function會用到的參數先load到register，等jump到function區塊里時再將代表augment的register存入function的stack memory區塊。

	<observation 5>
	0000006c <sub>:
		.
		.
	  7c:	4618      	mov	r0, r3	  			return d-c;
			//r3為代表sub(d,c)運算結果register
根據arm架構ABI,function回傳數值一律將數值存入 ro。


