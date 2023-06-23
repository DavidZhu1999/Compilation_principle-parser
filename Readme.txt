How to run the code:
严重性	代码	说明	项目	文件	行	禁止显示状态	禁止显示状态
错误	C4996	'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. 

这个错误是vs15即以后的版本使用的是c11, 所以fopen出现了版本问题

解决方法

在scanner.c中菜单栏项目-> complications1属性->C/C++ ->预处理器->预处理器定义添加_CRT_SECURE_NO_WARNINGS后即可运行

需要在code目录下增加一个input.txt才能运行

我们将一个已经配置过后的工程一并上传，可以直接使用这个工程来进行测试文件输入，文件夹名位project



Acheived Features：

1.Successfully get the token according to the rule of the N_language and match the right tpye and stirng.
2.Implements double-linklist(C language) function to store token which we segment.
3.Successfully analyze the five provided N_language_samples and display the right result.(Kindly refer to the .txt to check the result)
4.Could deal with some errors easy and common, such as some unknown characters and some illegal ruels of the N language.
5.Draw a DFA graph by using the JFLAP.
6.Write a DNA_Readme.txt to get understood more easily.
7.Almost Complete and implement the all requirements of this project followed by 4 provided PDF file. 
8.Code is as simple as possible and is added the detaied notes.


Problems：

1.'*' is a pointer or a plus operator that we haven't implemented to differ them.
2.Error analysis is not perfect, such as some seperators if necessarily appear in a pair together? (Maybe it's the tasks for parser)


Workload Share and contribution:

1.Code
    --Wu,Xiang and Zhu,ZheHao mainly
	  Wu,Xiang:   provides the code framework and early code logical, and implements a sucessful "array version" scanner
	  Zhu,ZheHao: implements the double-linklist function and improves the previous version to a sucessful "linklist version" scanner
      (Fianlly, Wu,Xiang, Zhu,ZheHao and Zhao,ZhuoYue check and amend together)

2.DFA and DFA_Readme
    --Zhao,ZhuoYue mainly
      (Finally, Zhao,ZhuoYue, Wu,Xiang and Zhu,ZheHao check and amend together)

3.Readme.txt
    --Wu,Xiang, Zhao,ZhuoYue and Zhu,ZheHao write together
	
Ps: Everyone is diligent and try hard to think and discuss, and finally complete this project.
    