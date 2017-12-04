#!/usr/bin/python3
# 队列，先进先出
# 双头链表实现

class Node(object):
    value = None
    next = None

    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next


class Queue:
    __head = None  # 头节点
    __tail = None  # 尾节点
    __size = 0

    def __init__(self, initial_capacity=10):
        if initial_capacity < 0:
            raise Exception("Illegal capacity")
        self.__max_size = initial_capacity

    def append(self, value):
        if self.__size >= self.__max_size:
            raise Exception("Queue is full!")
        new_node = Node(value)
        if self.__head is None:
            self.__head = new_node
            self.__tail = new_node
        else:
            self.__tail.next = new_node
            self.__tail = self.__tail.next

        self.__size += 1

    def remove(self):
        if self.__size == 0:
            return None
        temp_node = self.__head
        self.__head = self.__head.next
        if self.__head is None:  # 队列中没有数据了
            self.__tail = None
        self.__size -= 1
        return temp_node.value

    def index(self, index):
        if index < 0 or index > self.__size:
            raise Exception("Illegal index")  # 抛出异常
        if index == 0:
            return self.__head.value
        if index == self.__size - 1:
            return self.__tail.value

        temp_node = self.__head
        temp_index = 0
        while temp_node is not None and temp_index < index:
            temp_node = temp_node.next
            temp_index += 1

        if temp_node is None:
            return None
        else:
            return temp_node.value

    def size(self):
        return self.__size
