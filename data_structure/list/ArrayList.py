#!/usr/bin/python3
# 数组构成的线性表，参考 Java 中的 ArrayList

class ArrayList(object):
    """数组构成的线性表，参考 Java 中的 ArrayList"""

    __size = 0

    def __init__(self, initial_capacity=10):
        if initial_capacity < 0:
            raise Exception("Illegal capacity")  # 抛出异常

        self.__max_size = initial_capacity  # 数据个数
        self.__element_data = [None] * self.__max_size  # 内部数组，用于存放数据

    def put(self, index, element):
        self.__check_index(index)
        self.__element_data[index] = element
        pass

    def get(self, index):
        """支持反向查找"""
        self.__check_index(index)
        return self.__element_data[index]

    def size(self):
        return self.__size

    def remove(self, index):
        self.__check_index(index)
        self.__element_data.pop(index)
        pass

    def clear(self):
        self.__element_data.clear()
        self.__max_size = 0
        pass

    def __check_index(self, index):
        """检查索引范围"""
        if index < -self.__max_size or index >= self.__max_size:
            raise Exception("Illegal index")  # 抛出异常
