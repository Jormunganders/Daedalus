#!/usr/bin/python3
# 栈，后进先出
# 双头链表实现

class Node(object):
    value = None
    next = None

    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next


class Stack:
    __head = None  # 头节点
    __tail = None  # 尾节点
    __size = 0

    def __init__(self, initial_capacity=10):
        if initial_capacity < 0:
            raise Exception("Illegal capacity")
        self.__max_size = initial_capacity

    def push(self, value):
        if self.__size >= self.__max_size:
            raise Exception("Stack is full!")
        new_node = Node(value)
        if self.__tail is None:  # 没有数据
            self.__head = new_node
            self.__tail = self.__head
        else:
            self.__tail.next = new_node
            self.__tail = self.__tail.next

        self.__size += 1

    def pop(self):
        if self.__size == 0:
            return None
        temp_node = self.__head
        # 获取尾部节点的前一个节点
        while temp_node.next is not self.__tail:
            temp_node = temp_node.next

        old_tail_node = self.__tail
        self.__tail = temp_node
        self.__size -= 1
        return old_tail_node

    def size(self):
        return self.__size
