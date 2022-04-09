#include <initializer_list>
#include <memory>
#include <utility>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace zrb::interview_problems
{

template < typename T >
struct sll_t
{
    struct node_t
    {
        using ptr_t = std::shared_ptr < node_t >;

        T v_{};
        ptr_t next_{};
    };

    using node_ptr_t = typename node_t::ptr_t;

    template < typename U >
    constexpr sll_t(std::initializer_list < U > && l)
    {
        for (auto && i : l)
            emplace_back(i);
    }

    constexpr sll_t(node_ptr_t first) : first_(std::move(first))
    {
    }

    template < typename... Args >
    constexpr void emplace_back(Args &&... args)
    {
        auto && curr = std::make_shared < node_t >(node_t{T{ std::forward < Args >(args)...}, nullptr});

        if (first_ == nullptr)
            first_ = curr;
        
        if (last_ != nullptr)
            last_->next_ = curr;

        last_ = curr;
    }

    constexpr bool empty() const
    {
        return first_ == nullptr;
    }

    constexpr auto size() const
    {
        size_t i = 0;
        auto curr = first_;
        while (curr != nullptr)
        {
            ++i;
            curr = curr->next_;
        }
        return i;
    }

    //  'n' is 0-based
    constexpr auto nth_node(std::size_t const n) const
    {
        size_t i = 0;
        auto curr = first_;
        while (curr != nullptr && i < n)
        {
            ++i;
            curr = curr->next_;
        }
        return curr;
    }

    //  merge another list, starting from the node index 'i'
    constexpr void merge(sll_t & o, size_t i = 0)
    {
        if (auto n = o.nth_node(i); n != nullptr)
        {
            last_->next_ = n;
            last_ = o.last_;
        }
    }

    node_ptr_t first_{};
    node_ptr_t last_{};
};

template < typename T >
sll_t(std::initializer_list<T> &&) -> sll_t < T >;

template < typename T >
auto find_merge_point(sll_t < T > const & l1, sll_t < T > const & l2)
{
    auto const sz1 = l1.size();
    auto const sz2 = l2.size();
    auto const start1 = sz1 > sz2 ? sz1 - sz2 : 0;
    auto const start2 = sz1 > sz2 ? 0 : sz2 - sz1;
    auto n1 = l1.nth_node(start1);
    auto n2 = l2.nth_node(start2);
    auto i = 0LL;
    while (n1.get() != n2.get())
    {
        n1 = n1->next_;
        n2 = n2->next_;
        ++i;
    }
    return std::pair{start1 + i, start2 + i};
}

template < typename T >
std::ostream & operator << (std::ostream & os, sll_t < T > const & l)
{
    auto n = l.first_;
    os << '[' << std::endl;
    while (n != nullptr)
    {
        os << '(' << std::hex << n.get() << ", " << std::dec << n->v_ << ", " << std::hex << n->next_.get() << ')' << std::dec << std::endl;
        n = n->next_;
    }
    os << ']' << std::endl;
    return os;
}

}

using namespace zrb::interview_problems;

#include <catch2/catch.hpp>

namespace Catch
{

template < typename T >
struct StringMaker < std::pair < T, T > >
{
    static std::string convert(std::pair < T, T > const& p)
    {
        std::ostringstream oss;
        oss << "{" << p.first << ", " << p.second << "}";
        return oss.str();
    }
};

}

TEST_CASE("singly linked list find merge point", "[singly_linked_list_find_merge_point]")
{
    SECTION("basics")
    {
        sll_t l{{0, 1, 2}};
        REQUIRE(l.size() == 3);
        auto n2 = l.nth_node(2);
        REQUIRE(n2 != nullptr);
        REQUIRE(n2->v_ == 2);
        auto n3 = l.nth_node(3);
        REQUIRE(n3 == nullptr);
    }
    SECTION("append")
    {
        sll_t l1{{0, 1, 2}};
        sll_t l2{{3, 4, 5, 6}};
        l1.merge(l2);
        REQUIRE(l1.size() == 7);
        REQUIRE(l2.size() == 4);
    }
    SECTION("merge")
    {
        sll_t l1{{0, 1, 2}};
        sll_t l2{{0, 1, 2, 3, 4, 5, 6}};
        l1.merge(l2, 3);
        REQUIRE(l1.size() == 7);
        REQUIRE(l2.size() == 7);
    }
    SECTION("merge_past_end")
    {
        sll_t l1{{0, 1, 2, 3, 4, 5, 6}};
        sll_t l2{{0, 1, 2}};
        l1.merge(l2, 3);
        REQUIRE(l1.size() == 7);
        REQUIRE(l2.size() == 3);
    }
    SECTION("find_merge_point_after_append")
    {
        sll_t l1{{0, 1, 2, 3}};
        sll_t l2{{4, 5, 6}};
        l1.merge(l2);
        REQUIRE(find_merge_point(l1, l2) == std::pair{4ull, 0ull});
        REQUIRE(find_merge_point(l2, l1) == std::pair{0ull, 4ull});
    }
    SECTION("find_merge_point_after_merge")
    {
        sll_t l1{{0, 1, 2, 3}};
        sll_t l2{{0, 1, 2, 3, 4, 5, 6}};
        l1.merge(l2, 4);
        REQUIRE(find_merge_point(l1, l2) == std::pair{4ull, 4ull});
        REQUIRE(find_merge_point(l2, l1) == std::pair{4ull, 4ull});
    }
    SECTION("find_merge_point_after_merge_past_end")
    {
        sll_t l1{{0, 1, 2, 3, 4, 5, 6}};
        sll_t l2{{0, 1, 2, 3}};
        l1.merge(l2, 4);
        REQUIRE(find_merge_point(l1, l2) == std::pair{7ull, 4ull});
        REQUIRE(find_merge_point(l2, l1) == std::pair{4ull, 7ull});
    }
    SECTION("find_merge_point_after_merge_at_end")
    {
        sll_t l1{{0, 1, 2, 3, 4, 5}};
        sll_t l2{{0, 1, 2, 3, 4, 5, 6}};
        l1.merge(l2, l1.size());
        REQUIRE(find_merge_point(l1, l2) == std::pair{6ull, 6ull});
        REQUIRE(find_merge_point(l2, l1) == std::pair{6ull, 6ull});
    }
}
