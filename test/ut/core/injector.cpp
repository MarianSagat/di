//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "boost/di/injector.hpp"
#include "boost/di/core/injector.hpp"
#include "common/fakes/fake_dependency.hpp"
#include "common/fakes/fake_config.hpp"

namespace boost { namespace di { namespace core {

test def_ctor = [] {
    injector<di::config> injector;
    expect(std::is_same<aux::type_list<>, decltype(injector)::deps>{});
};

test ctor = [] {
    using dep1 = fake_dependency<int>;
    using dep2 = fake_dependency<double>;
    injector<di::config, dep1, dep2> injector;
};

test ctor_injector = [] {
    injector<di::config> injector1;
    injector<di::config> injector2{injector1};
    (void)injector2;
};

test create = [] {
    injector<di::config> injector{};
    expect_eq(0, injector.create_impl<int>());
};

test call = [] {
    fake_scope<>::entry_calls() = 0;
    fake_scope<>::exit_calls() = 0;

    using dep1 = fake_dependency<int>;
    injector<di::config, dep1> injector;

    injector.call(fake_scope_entry{});
    expect_eq(1, fake_scope<>::entry_calls());

    injector.call(fake_scope_exit{});
    expect_eq(1, fake_scope<>::exit_calls());
};

}}} // boost::di::core

