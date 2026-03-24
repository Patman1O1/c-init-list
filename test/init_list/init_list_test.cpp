#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/init_list/init_list.h"

namespace init_list_tests {
    // ── Method Tests (init_list_init) ────────────────────────────────────────────────────────────────────────────────
    TEST(init_list_init, empty_init_list) {
        struct ::init_list init_list;
        init_list_init(int, init_list, 0);

        EXPECT_EQ(init_list.size, 0);
        EXPECT_EQ(init_list.values_p, nullptr);

        init_list_free(&init_list);
    }

    TEST(init_list_init, single_value_init_list) {
        struct ::init_list init_list;
        init_list_init(int, init_list, 1, 1);

        EXPECT_EQ(init_list.size, 1);
        EXPECT_NE(init_list.values_p, nullptr);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));

        ::init_list_free(&init_list);
    }

    TEST(init_list_init, multi_value_init_list) {
        struct ::init_list init_list;

        init_list_init(int, init_list, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(init_list.size, 5);
        EXPECT_NE(init_list.values_p, nullptr);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));
        EXPECT_EQ(2, init_list_at(int, init_list, 1));
        EXPECT_EQ(3, init_list_at(int, init_list, 2));
        EXPECT_EQ(4, init_list_at(int, init_list, 3));
        EXPECT_EQ(5, init_list_at(int, init_list, 4));

        ::init_list_free(&init_list);
    }

    // ── Method Tests (init_list_init1) ────────────────────────────────────────────────────────────────────────────────
    TEST(init_list_init1, empty_init_list) {
        struct ::init_list init_list = init_list_init1(int, 0);

        EXPECT_EQ(init_list.size, 0);
        EXPECT_EQ(init_list.values_p, nullptr);

        init_list_free(&init_list);
    }

    TEST(init_list_init1, single_value_init_list) {
        struct ::init_list init_list = init_list_init1(int, 1, 1);

        EXPECT_EQ(init_list.size, 1);
        EXPECT_NE(init_list.values_p, nullptr);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));

        ::init_list_free(&init_list);
    }

    TEST(init_list_init1, multi_value_init_list) {
        struct ::init_list init_list = init_list_init1(int, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(init_list.size, 5);
        EXPECT_NE(init_list.values_p, nullptr);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));
        EXPECT_EQ(2, init_list_at(int, init_list, 1));
        EXPECT_EQ(3, init_list_at(int, init_list, 2));
        EXPECT_EQ(4, init_list_at(int, init_list, 3));
        EXPECT_EQ(5, init_list_at(int, init_list, 4));

        ::init_list_free(&init_list);
    }

    // ── Method Tests (init_list_at) ──────────────────────────────────────────────────────────────────────────────────
    TEST(init_list_at, single_value_init_list) {
        struct ::init_list init_list;
        init_list_init(int, init_list, 1, 1);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));

        init_list_free(&init_list);
    }

    TEST(init_list_at, multi_value_init_list) {
        struct ::init_list init_list;
        init_list_init(int, init_list, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(1, init_list_at(int, init_list, 0));
        EXPECT_EQ(2, init_list_at(int, init_list, 1));
        EXPECT_EQ(3, init_list_at(int, init_list, 2));
        EXPECT_EQ(4, init_list_at(int, init_list, 3));

        ::init_list_free(&init_list);
    }

    // ── Method Tests (init_list_cmp) ─────────────────────────────────────────────────────────────────────────────────
    TEST(init_list_cmp, lhs_null) {
        struct ::init_list rhs;
        init_list_init(int, rhs, 0);

        EXPECT_EQ(EFAULT, init_list_cmp(nullptr, &rhs));
        EXPECT_EQ(EFAULT, errno);
    }

    TEST(init_list_cmp, rhs_null) {
        struct ::init_list lhs;
        init_list_init(int, lhs, 0);

        EXPECT_EQ(EFAULT, init_list_cmp(&lhs, nullptr));
        EXPECT_EQ(EFAULT, errno);
    }

    TEST(init_list_cmp, lhs_empty__rhs_filled) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 0);
        init_list_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, init_list_cmp(&lhs, &rhs));

        ::init_list_free(&rhs);
    }

    TEST(init_list_cmp, lhs_filled__rhs_empty) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 5, 1, 2, 3, 4, 5);
        init_list_init(int, rhs, 0);

        EXPECT_EQ(1, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
    }

    TEST(init_list_cmp, both_filled__lhs_size_larger) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 5, 1, 2, 3, 4, 5);
        init_list_init(int, rhs, 1, 6);

        EXPECT_EQ(1, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
        init_list_free(&rhs);
    }

    TEST(init_list_cmp, both_filled__rhs_size_larger) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 1, 1);
        init_list_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
        init_list_free(&rhs);
    }

    TEST(init_list_cmp, both_filled__both_sizes_equal__lhs_values_greater) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 5, 6, 7, 8, 9, 10);
        init_list_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(1, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
        init_list_free(&rhs);
    }

    TEST(init_list_cmp, both_filled__both_sizes_equal__rhs_values_greater) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 5, 1, 2, 3, 4, 5);
        init_list_init(int, rhs, 5, 6, 7, 8, 9, 10);

        EXPECT_EQ(-1, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
        init_list_free(&rhs);
    }

    TEST(init_list_cmp, both_filled__both_sizes_equal__both_values_equal) {
        struct ::init_list lhs, rhs;

        init_list_init(int, lhs, 5, 1, 2, 3, 4, 5);
        init_list_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(0, init_list_cmp(&lhs, &rhs));

        init_list_free(&lhs);
        init_list_free(&rhs);
    }

} // namespace init_list_tests
