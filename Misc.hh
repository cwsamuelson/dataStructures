#ifndef __MISC_H__
#define __MISC_H__

#ifdef  DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

namespace Jing{

#define debug_print(fmt)\
        do{if(DEBUG_TEST) fprintf(stderr, "%s:%d:%s() " fmt, __FILE__,\
                            __LINE__,__func__);} while(0)

//Allows for template parameter constraints, used as:
/*
  template<class Container>
        void draw_all(Container& c)
        {
                typedef typename Container::value_type T;
                Can_copy<T,Shape*>(); // accept containers of only Shape*s

                for_each(c.begin(),c.end(),mem_fun(&Shape::draw));
        }
*/
//http://www.stroustrup.com/bs_faq2.html#constraints
template<class T1, class T2> struct can_copy{
  static void constraints(T1 a, T2 b) { T2 c = a; b = a;}
  can_copy() { void(*p) (T1,T2) = constraints; }
};

}

#endif

