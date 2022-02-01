/*
Communication utility functions
(c) Tom Powell 2021, under the GPL
*/
#include "ansicodes.hpp"
using namespace ANSI;

template <class t>
void sendWarn(const char* head, const char* msg, t where){ 
    where.println(bk::d_yellow);
    where.println(fr::l_white);
    where.println(head);
    where.println(reset);
    where.println(msg);
} 
template <class t>
void sendErr(const char* head, const char* msg, t where){
    where.println(bk::d_red);
    where.println(fr::l_white);
    where.println(head);
    where.println(reset);
    where.println(msg)
}
template <class t>
void sendGood(const char* head, const char* msg, t where){
    where.println(bk::l_green);
    where.println(fr::l_white);
    where.println(head);
    where.println(reset);
    where.println(msg);
}
template <class t>
void sendInfo(const char* head, const char* msg, t where){
    where.println(bk::l_white);
    where.println(fr::d_black);
    where.println(head);
    where.println(reset);
    where.println(msg);
}
template <typename t, class T>
void sendVector(t vec, T where){
    where.println("X: ");
    where.println(vec.x);
    where.println("Y: ");
    where.println(vec.y);
    where.println("Z: ");
    where.println(vec.z);
}