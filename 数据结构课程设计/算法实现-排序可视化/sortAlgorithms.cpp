#include "sortAlgorithms.h"

sortAlgorithms::sortAlgorithms()
{
    stop = 1;    // 初始不在排序状态
    cmpCnt = 0;     // 初始化比较次数
    oprtCnt = 0;
    oneStep = 0;    // 初始非单步执行状态
    pause = 0;
}

sortAlgorithms::~sortAlgorithms()
{

}

// 是否正在排序
bool sortAlgorithms::isSorting()
{
    if(stop || sortingDone) return false;
    return true;
}

// 是否处于单步执行状态
bool sortAlgorithms::isOneStep()
{
    return oneStep;
}

// 是否处于暂停状态
bool sortAlgorithms::isPause()
{
    return pause;
}

// 设置排序状态
void sortAlgorithms::setSortingState(bool state)
{
    sortingDone = !state;
}

// 设置是否单步排序
void sortAlgorithms::setOneStepState(bool state)
{
    oneStep = state;
}

// 设置排序演示速度
void sortAlgorithms::setSpeed(int speed)
{
    this->speed = speed;
}

// 设置排序属性
void sortAlgorithms::setAttribute(int dataNum, int *numbers, int algorithmSelected, int speed)
{
    this->dataNum = dataNum;
    this->numbers = numbers;
    this->algorithmSelected = algorithmSelected;
    this->speed = speed;
//    this->stop = false;     // 排序即将开始，若当前处于停止状态需要置成false
}

// 获取比较次数
int sortAlgorithms::getCmpCnt()
{
    return cmpCnt;
}

// 获取交换次数
int sortAlgorithms::getOprtCnt()
{
    return oprtCnt;
}

// 停止排序线程
void sortAlgorithms::stopSorting()
{
    stop = true;
}

// 暂停排序
void sortAlgorithms::pauseSorting()
{
    //qDebug()<<"暂停排序";
    if(!pause)
    {
        this->pauseLock.lock();
        pause = true;
    }
}

// 继续排序
void sortAlgorithms::resumeSorting()
{
    //qDebug()<<"继续排序";
    if(pause)
    {
        this->pauseLock.unlock();
        pause = false;
    }
}

void sortAlgorithms::run()
{
    stop = false;
    while(!stop && !sortingDone)
    {
        process();
    }
    quit();
    wait();

}


void sortAlgorithms::process()
{
    // 重置比较和交换次数
    cmpCnt = 0;
    oprtCnt = 0;

    // 调用各种排序的函数
    switch (algorithmSelected)
    {
    case 0:     // 插入排序
        while(!stop && !sortingDone)
        {
            insertSort();
            if(stop) return;
            sortingDone = 1;
        }
        break;

    case 1:     // 折半插入排序
        while(!stop && !sortingDone)
        {
            halfinsertSort();
            if(stop) return;
            sortingDone = 1;
        }
        break;

    case 2:     // 希尔排序
        while(!stop && !sortingDone)
        {
            shellSort();
            if(stop) return;
            sortingDone = 1;
        }
        break;

    case 3:     //冒泡排序
        while(!stop && !sortingDone)
        {
            bubbleSort();
            if(stop) return;
            sortingDone = 1;
        }
        break;

    case 4:     // 快速排序
        while(!stop && !sortingDone)
        {
            quickSort(0, dataNum - 1);
            if(stop) return;
            sortingDone = 1;
        }
        break;

    case 5:     // 选择排序
        while(!stop && !sortingDone)
        {
            selectSort();
            if(stop) return;
            sortingDone = 1;
        }
        break;
    }

    //排序结束，发送结束的信号
    emit showSBMsg(1, QString("排序已完成"));
    emit showSBMsg(2, QString(""));     // 清空操作和描述
    emit showSBMsg(3, QString(""));
    emit showSBMsg(4, QString(""));
    emit sortFinish();
    stop = true;
}



// 交换a b两个位置的数
void sortAlgorithms::swap(int a, int b)
{
    oprtCnt++;//维护交换次数
    //交换两数
    int t = numbers[a];
    numbers[a] = numbers[b];
    numbers[b] = t;
}




// 0 插入排序
void sortAlgorithms::insertSort()
{
    for(int i = 1; i < dataNum; i++)
    {
        if(stop) return;

        int key = numbers[i];
        int j = i - 1;

        pauseLock.lock();
        pauseLock.unlock();
        emit baseColumn(i);
        emit showSBMsg(2, QString("更新待插入元素 %1 -> %2 ").arg(j).arg(j+1));
        emit showSBMsg(3, QString("寻找合适位置，将待插入元素插入到有序序列中"));
        emit showSBMsg(4, QString("当前待插入：i = %1").arg(i));
        msleep(speed);

        while(j >= 0 && numbers[j] > key)
        {
            if(stop) return;

            pauseLock.lock();
            pauseLock.unlock();
            cmpCnt++;
            emit showSBMsg(2, QString("比较：j = %1, i = %2").arg(j).arg(i));
            emit compareColumn(i, j);
            emit baseColumn(i);
            msleep(speed);

            numbers[j+1] = numbers[j];

            oprtCnt++;
            emit updtColumn(j+1, true, numbers);
            emit showSBMsg(2, QString("j = %1 后移1位").arg(j));
            emit compareColumn(i, j);       // 避免颜色被覆盖，下同
            emit baseColumn(i);
            msleep(speed);
            if(oneStep) resumeSorting();    // 单步执行时此处不暂停，一个基准值作为一步，否则过程逻辑展现不清晰

            j--;
        }
        numbers[j+1] = key;

        oprtCnt++;
        emit updtColumn(j+1, true, numbers);
        emit showSBMsg(2, QString("已找到合适位置，插入 i "));
        msleep(speed);

    }
}

// 1 折半插入
void sortAlgorithms::halfinsertSort()
{
    for(int i = 1; i < dataNum; i++)
    {
        if(stop) return;

        int key = numbers[i];
        int j = i - 1;

        pauseLock.lock();
        pauseLock.unlock();
        emit baseColumn(i);
        emit showSBMsg(2, QString("更新待插入元素 %1 -> %2 ").arg(j).arg(j+1));
        emit showSBMsg(3, QString("寻找合适位置，将待插入元素插入到有序序列中"));
        emit showSBMsg(4, QString("当前待插入：i = %1").arg(i));
        msleep(speed);

        int l=-1,r=j;
        while(l<r){
            if(stop) return;
            pauseLock.lock();
            pauseLock.unlock();
            cmpCnt++;

            int mid = (l+r+1)/2;
            emit showSBMsg(2, QString("比较：j = %1, i = %2").arg(j).arg(i));
            emit compareColumn(i, j);
            emit baseColumn(i);
            msleep(speed);

            emit compareColumn(i, mid);       // 避免颜色被覆盖，下同

            if(numbers[mid]>key){
                for(int u=r;u>=mid;u--){
                    numbers[u+1]=numbers[u];
                    oprtCnt++;
                    emit updtColumn(u+1, true, numbers);
                    emit showSBMsg(2, QString("u = %1 后移1位").arg(j));
                    emit baseColumn(i);
                    msleep(speed);
                    if(oneStep) resumeSorting();    // 单步执行时此处不暂停，一个基准值作为一步，否则过程逻辑展现不清晰
                }
                r=mid-1;
            }
            else{
                emit baseColumn(i);
                msleep(speed);
                if(oneStep) resumeSorting();    // 单步执行时此处不暂停，一个基准值作为一步，否则过程逻辑展现不清晰
                l=mid;
            }
        }
/*
 insertSort:
        while(j >= 0 && numbers[j] > key)
        {
            if(stop) return;

            pauseLock.lock();
            pauseLock.unlock();
            cmpCnt++;
            emit showSBMsg(2, QString("比较：j = %1, i = %2").arg(j).arg(i));
            emit compareColumn(i, j);
            emit baseColumn(i);
            msleep(speed);

            numbers[j+1] = numbers[j];

            oprtCnt++;
            emit updtColumn(j+1, true, numbers);
            emit showSBMsg(2, QString("j = %1 后移1位").arg(j));
            emit compareColumn(i, j);       // 避免颜色被覆盖，下同
            emit baseColumn(i);
            msleep(speed);
            if(oneStep) resumeSorting();    // 单步执行时此处不暂停，一个基准值作为一步，否则过程逻辑展现不清晰

            j--;
        }
*/

        numbers[l+1] = key;

        oprtCnt++;
        emit updtColumn(l+1, true, numbers);
        emit showSBMsg(2, QString("已找到合适位置，插入 i "));
        msleep(speed);
    }
}

// 2 希尔排序
void sortAlgorithms::shellSort()
{

    int i, j;
    for(int gap = dataNum >> 1; gap >= 1; gap = gap >> 1)
    {
        if(stop) return;

        emit showSBMsg(4, QString("gap = %1").arg(gap));
        pauseLock.lock();
        pauseLock.unlock();
        for(i = gap; i < dataNum; i++)
        {
            if(stop) return;

            pauseLock.lock();
            pauseLock.unlock();
            cmpCnt++;
            emit showSBMsg(2, QString("比较：i = %1, j = %2").arg(i).arg(i-gap));
            emit showSBMsg(3, QString("判断当前数是否需要移动"));
            emit compareColumn(i, i-gap);
            msleep(speed);

            if (numbers[i] < numbers[i - gap])  // i小于同组前面的数，把i用冒泡交换至同组前面合适的位置
            {

                int temp = numbers[i];
                for(j = i - gap; j >= 0 && numbers[j] > temp; j = j - gap)
                {
                    if(stop) return;

                    if(j != i-gap)  // 第一次进入循环不暂停和计数，否则与上面的暂停计数重复
                    {
                        pauseLock.lock();
                        pauseLock.unlock();
                        cmpCnt++;
                        emit showSBMsg(2, QString("比较：i = %1, j = %2").arg(i).arg(j));
                        emit showSBMsg(3, QString("寻找同组中 i 可以移动的最前位置"));
                        emit compareColumn(i, j);
                        msleep(speed);
                    }
                    numbers[j + gap] = numbers[j];  // 冒泡逐个更新值

                    pauseLock.lock();
                    pauseLock.unlock();
                    oprtCnt++;
                    emit compareColumn(j, j+gap);       //仅用于指示变量，无比较意义
                    emit showSBMsg(2, QString("比较：i = %1, j = %2").arg(i).arg(j));
                    emit showSBMsg(3, QString("寻找同组中 i 可以移动的最前位置"));
                    pauseLock.lock();
                    pauseLock.unlock();
                    emit updtColumn(j+gap, false, numbers); // 更新一个值且不覆盖上次的颜色，视觉上是同组蓝色比较后同组都是红色更新值，不会一次只显示一个
                    emit showSBMsg(2, QString("移动：%1 -> %2").arg(j).arg(j+gap));
                    emit showSBMsg(3, QString("类似冒泡，移动中间变量，给 i 让出空间"));
                    msleep(speed);
                }
                numbers[j + gap] = temp;    // 原来的i移动到合适的位置

                oprtCnt++;
                pauseLock.lock();
                pauseLock.unlock();
                emit showSBMsg(2, QString("移动：%1 -> %2").arg(i).arg(j+gap));
                emit showSBMsg(3, QString("移动 i 到同组中满足条件的最靠前位置"));
                emit compareColumn(i, j+gap);       //仅用于指示变量，无比较意义
                emit updtColumn(j+gap, true, numbers);
                msleep(speed);
            }
        }
    }
}

// 3 冒泡排序
void sortAlgorithms::bubbleSort()
{
    for (int i = 0; i < dataNum; i++)
    {
        emit showSBMsg(4, QString("第 %1 轮").arg(i+1));
        for (int j = 0; j < dataNum - 1 - i; j++)
        {
            if(stop) return;

            pauseLock.lock();
            pauseLock.unlock();

            cmpCnt++;
            if(oneStep)
            {
                pauseLock.lock();
                pauseLock.unlock();
                emit compareColumn(j, j + 1);
                emit baseColumn(j);     // 指示当前位置颜色
                msleep(speed);
            }
            emit showSBMsg(2, QString("当前下标 %1   比较%2, %3 ").arg(j).arg(j).arg(j+1));

            if (numbers[j] > numbers[j + 1])
            {
                swap(j, j + 1);

                pauseLock.lock();
                pauseLock.unlock();
                emit swapColumn(j, j + 1, numbers);
                emit showSBMsg(2, QString("交换：%1, %2 ").arg(j).arg(j+1));
                msleep(speed);
            }
        }
    }

}

// 4 快速排序
void sortAlgorithms::quickSort(int left, int right)
{
    if(stop) return;    // 用于用户在排序时点击 重新生成数据 或 退出程序 后，立即停止当前排序，并根据需要开始新的排序
    if(left >= right) return;

    int i, j, base;     // 左右指针，基准
    i = left, j = right;
    base = numbers[left];     // 第一个值设为基准
    if(oneStep) {emit baseColumn(left); msleep(speed); }

    emit showSBMsg(4, QString("排序区间[%1, %2]，base：%3").arg(left).arg(right).arg(left));

    while(i < j)
    {
        if(stop) return;
        pauseLock.lock();           // 每个代码段都需要这两句保证暂停按钮/单步执行时暂停生效
        pauseLock.unlock();

        emit showSBMsg(2, QString("i = %1, j = %2 相遇后本轮结束").arg(i).arg(j));
        if(oneStep) {emit baseColumn(left); msleep(speed); resumeSorting(); }    // 防止新进入循环时基准颜色被覆盖

        while(numbers[j] >= base && i < j)  // 先j后i，保证一轮之后基准值左侧都是小于基准值的数，先i后j不能保证
        {
            j--;
            cmpCnt++;                 // 只统计元素数值比较次数，不统计指针i j自身的大小比较次数
            pauseLock.lock();
            pauseLock.unlock();
            emit showSBMsg(2, QString("i = %1, j = %2 相遇后本轮结束").arg(i).arg(j));
            emit showSBMsg(3, QString("移动 j 指针与base比较，找<base的位置"));
            if(oneStep){emit baseColumn(left); emit compareColumn(i, j); if(i != left){ emit baseColumn(left);resumeSorting();} msleep(speed);}
        }
        while(numbers[i] <= base && i < j)
        {
            i++;
            cmpCnt++;
            pauseLock.lock();
            pauseLock.unlock();
            emit showSBMsg(2, QString("i = %1, j = %2 相遇后本轮结束").arg(i).arg(j));
            emit showSBMsg(3, QString("移动 i 指针与base比较，找>base的位置"));
            if(oneStep){emit baseColumn(left); emit compareColumn(i, j); if(i != left){ emit baseColumn(left);resumeSorting();}  msleep(speed);}
        }

        if(i < j){
            swap(i, j);

            pauseLock.lock();
            pauseLock.unlock();
            qDebug() << "swap " << i << " " << j << endl;
            emit showSBMsg(2, QString("交换：%1 %2").arg(i).arg(j));
            emit showSBMsg(3, QString("交换指针，使最终base左侧小于base，右侧大于base"));
            emit swapColumn(i,j,numbers);
            emit baseColumn(left);
            resumeSorting();
            msleep(speed);
        }
    }

    numbers[left] = numbers[i];
    numbers[i] = base;
    oprtCnt++;
    emit swapColumn(left, i, numbers);    // 交换位于首位的基准值和指针相遇位置
    emit showSBMsg(2, QString("交换：%1 %2").arg(left).arg(i));
    emit showSBMsg(3, QString("交换基准值和指针相遇位置"));
    emit showSBMsg(4, QString("排序区间[%1, %2]，base：%3").arg(left).arg(right).arg(i));
    msleep(speed);

    quickSort(left, i - 1);
    quickSort(i + 1, right);

}

// 5 选择排序
void sortAlgorithms::selectSort()
{
    for(int i = 0; i < dataNum - 1; i++)	// 控制排序的轮数，每一轮新增一个排好序的元素
    {
        if(stop) return;


        int min = numbers[i], min_flag = i;

        pauseLock.lock();
        pauseLock.unlock();
        emit showSBMsg(4, QString("第 %1 轮").arg(i+1));
        emit baseColumn(min_flag); // 指示最小值
        msleep(speed);

        for(int j = i + 1; j < dataNum; j++)	// 遍历未排好序的序列，找出最小值
        {
            if(stop) return;

            if(!oneStep)    // 此处加锁为了暂停排序功能。单步执行时找到新的最小值为一步，不需要在这停下
            {
                pauseLock.lock();
                pauseLock.unlock();
            }

            cmpCnt++;       // 下面j与最小值比较
            emit showSBMsg(2, QString("比较：j = %1, min_pos = %2 ").arg(j).arg(min_flag));
            emit showSBMsg(3, QString("查找无序序列中最小值"));
            emit compareColumn(min_flag, j);    // 指示j和当前最小值比较过程
            emit baseColumn(min_flag);          // 防止最小值颜色被覆盖
            msleep(speed);

            if(numbers[j] < min)        // 记录最小值以及下标
            {
                min = numbers[j];
                min_flag = j;

                pauseLock.lock();           // 单步执行时找到新的最小值为一步
                pauseLock.unlock();
                emit showSBMsg(2, QString("更新：min_pos = %1 ").arg(min_flag));
                emit showSBMsg(3, QString("找到更小的值，更新min_pos"));
                emit baseColumn(min_flag);  // 指示新的最小值
                msleep(speed);
            }
        }

        swap(i, min_flag);  // 交换i和最小值

        oprtCnt++;
        pauseLock.lock();
        pauseLock.unlock();
        emit showSBMsg(2, QString("交换：min_pos = %1, i = %2 ").arg(min_flag).arg(i));
        emit showSBMsg(3, QString("最小值交换到无序序列头部，有序序列长度+1"));
        emit swapColumn(i, min_flag, numbers);
        msleep(speed);
    }

}
