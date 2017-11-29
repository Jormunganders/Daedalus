#!/usr/bin/python3
# 数组构成的线性表，参考 Java 中的 ArrayList

class ArrayList(object):
    """数组构成的线性表，参考 Java 中的 ArrayList"""

    __size = 0

    def __init__(self, initial_capacity=10):
        if initial_capacity < 0:
            raise Exception("Illegal capacity")  # 抛出异常

        self.__max_size = initial_capacity  # 最大数据容量
        self.__element_data = [None] * self.__max_size  # 内部数组，用于存放数据

    def add(self, element):
        if self.__size >= self.__max_size:
            raise Exception("ArrayList is full!")
        self.__element_data[self.__size] = element
        self.__size += 1

    def update(self, index, new_element):
        self.__check_index(index)
        self.__element_data[index] = new_element

    def get(self, index):
        self.__check_index(index)
        return self.__element_data[index]

    def size(self):
        return self.__size

    def remove(self, index):
        self.__check_index(index)
        self.__element_data.pop(index)
        self.__size -= 1

    def clear(self):
        self.__element_data.clear()
        self.__size = 0
        pass

    def __check_index(self, index):
        """检查索引范围，不支持反向"""
        if index < 0 or index >= self.__size:
            raise Exception("Illegal index")  # 抛出异常
