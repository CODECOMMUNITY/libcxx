//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <memory>

// unique_ptr

// Test unique_ptr converting move assignment

#include <memory>
#include <utility>
#include <cassert>

struct A
{
    static int count;
    A() {++count;}
    A(const A&) {++count;}
    virtual ~A() {--count;}
};

int A::count = 0;

struct B
    : public A
{
    static int count;
    B() {++count;}
    B(const B&) {++count;}
    virtual ~B() {--count;}
};

int B::count = 0;

int main()
{
    {
    std::unique_ptr<B> s(new B);
    A* p = s.get();
    std::unique_ptr<A> s2(new A);
    assert(A::count == 2);
    s2 = std::move(s);
    assert(s2.get() == p);
    assert(s.get() == 0);
    assert(A::count == 1);
    assert(B::count == 1);
    }
    assert(A::count == 0);
    assert(B::count == 0);
}
