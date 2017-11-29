#!/usr/bin/python3
# 数组构成的线性表，参考 Java 中的 LinkedList
# 单链表

class LinkedList(object):
    __head = None  # 头结点
    __size = 0

    def __init__(self, initial_capacity=10):
        if initial_capacity < 0:
            raise Exception("Illegal capacity")
        self.__max_size = initial_capacity

    def add(self, value):
        if self.__size >= self.__max_size:
            raise Exception("LinkedList is full!")
        new_node = Node(value)
        if self.__head is None:
            self.__head = new_node
            self.__size = 1
        else:
            temp_node = self.__head
            while temp_node.next is not None:
                temp_node = temp_node.next
            temp_node.next = new_node
            self.__size += 1

    def insert(self, index, value):
        if index < 0 or index > self.__size:
            raise Exception("Illegal index")  # 抛出异常
        if self.__size >= self.__max_size:
            raise Exception("LinkedList is full!")
        new_node = Node(value)
        if index == 0:  # 插入到第一个位置
            new_node.next = self.__head
            self.__head = new_node
        else:
            node_map = self.__find(index)
            pre_node = node_map["prevent"]
            temp_node = node_map["current"]
            new_node.next = temp_node
            pre_node.next = new_node


    def update(self, index, value):
        self.__check_index(index)
        node_map = self.__find(index)
        target_node = node_map["current"]
        target_node.value = value


    def get(self, index):
        self.__check_index(index)
        node_map = self.__find(index)
        target_node = node_map["current"]
        return target_node.value


    def size(self):
        return self.__size


    def remove(self, index):
        self.__check_index(index)
        node_map = self.__find(index)
        target_node = node_map["current"]
        prev_node = node_map["prevent"]
        prev_node.next = target_node.next
        target_node = None


    def clear(self):
        temp_node = self.__head
        while temp_node is not None:
            rubbish = temp_node
            temp_node = temp_node.next
            rubbish = None
        self.__size = 0


    def __find(self, index):
        temp_node = self.__head
        temp_index = 0
        pre_node = None
        while temp_node.next is not None and temp_index < index:
            pre_node = temp_node
            temp_node = temp_node.next
            temp_index += 1

        return {"prevent": pre_node, "current": temp_node, "next": temp_node.next}


    def __check_index(self, index):
        """检查索引范围，不支持反向"""
        if index < 0 or index >= self.__size:
            raise Exception("Illegal index")  # 抛出异常


class Node(object):
    value = None
    next = None

    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next
