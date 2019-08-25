////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2013 Shuangyang Yang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/hpx_init.hpp>
#include <hpx/datastructures/any.hpp>
#include <hpx/testing.hpp>

#include <hpx/util/storage/tuple.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "small_big_object.hpp"

using hpx::util::any_nonser;
using hpx::util::any_cast;

using hpx::init;
using hpx::finalize;

///////////////////////////////////////////////////////////////////////////////
int hpx_main()
{
    {
        any_nonser any1(big_object(30, 40));
        std::stringstream buffer;

        buffer << any1;

        HPX_TEST_EQ(buffer.str(), "3040");
    }

    // non serializable version
    {
        // test equality
        {
            any_nonser any1_nonser(7), any2_nonser(7), any3_nonser(10),
                any4_nonser(std::string("seven"));

            HPX_TEST_EQ(any1_nonser, 7);
            HPX_TEST_NEQ(any1_nonser, 10);
            HPX_TEST_NEQ(any1_nonser, 10.0f);
            HPX_TEST_EQ(any1_nonser, any1_nonser);
            HPX_TEST_EQ(any1_nonser, any2_nonser);
            HPX_TEST_NEQ(any1_nonser, any3_nonser);
            HPX_TEST_NEQ(any1_nonser, any4_nonser);

            std::string long_str =
                std::string("This is a looooooooooooooooooooooooooong string");
            std::string other_str = std::string("a different string");
            any1_nonser = long_str;
            any2_nonser = any1_nonser;
            any3_nonser = other_str;
            any4_nonser = 10.0f;

            HPX_TEST_EQ(any1_nonser, long_str);
            HPX_TEST_NEQ(any1_nonser, other_str);
            HPX_TEST_NEQ(any1_nonser, 10.0f);
            HPX_TEST_EQ(any1_nonser, any1_nonser);
            HPX_TEST_EQ(any1_nonser, any2_nonser);
            HPX_TEST_NEQ(any1_nonser, any3_nonser);
            HPX_TEST_NEQ(any1_nonser, any4_nonser);
        }

        {
            if (sizeof(small_object) <= sizeof(void*))
                std::cout << "object is small\n";
            else
                std::cout << "object is large\n";

            small_object const f(17);

            any_nonser any1_nonser(f);
            any_nonser any2_nonser(any1_nonser);
            any_nonser any3_nonser = any1_nonser;

            HPX_TEST_EQ((any_cast<small_object>(any1_nonser)) (2), uint64_t(17+2));
            HPX_TEST_EQ((any_cast<small_object>(any2_nonser)) (4), uint64_t(17+4));
            HPX_TEST_EQ((any_cast<small_object>(any3_nonser)) (6), uint64_t(17+6));

        }

        {
            if (sizeof(big_object) <= sizeof(void*))
                std::cout << "object is small\n";
            else
                std::cout << "object is large\n";

            big_object const f(5, 12);

            any_nonser any1_nonser(f);
            any_nonser any2_nonser(any1_nonser);
            any_nonser any3_nonser = any1_nonser;

            HPX_TEST_EQ((any_cast<big_object>(any1_nonser)) (3,4), uint64_t(5+12+3+4));
            HPX_TEST_EQ((any_cast<big_object>(any2_nonser)) (5,6), uint64_t(5+12+5+6));
            HPX_TEST_EQ((any_cast<big_object>(any3_nonser)) (7,8), uint64_t(5+12+7+8));
        }

        // move semantics
        {
            any_nonser any1(5);
            HPX_TEST(!any1.empty());
            any_nonser any2(std::move(any1));
            HPX_TEST(!any2.empty());
            HPX_TEST(any1.empty()); // NOLINT
        }

        {
            any_nonser any1(5);
            HPX_TEST(!any1.empty());
            any_nonser any2;
            HPX_TEST(any2.empty());

            any2 = std::move(any1);
            HPX_TEST(!any2.empty());
            HPX_TEST(any1.empty()); // NOLINT
        }
    }

    finalize();
    return hpx::util::report_errors();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Initialize and run HPX
    return init(argc, argv);
}

