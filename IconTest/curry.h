#pragma once

#include <functional>
#include <utility>
#include <iostream>

namespace Reimuda {
    namespace {
        // ��I > 1ʱ��ʵ�������ģ��
        template <typename F, std::size_t I, typename T = std::tuple<>>
        class CurriedFunction {
        private:
            const F& _fn;
            T _cache;
            const static std::size_t i{ I };
        public:
            CurriedFunction(const F& f, T&& cache) :
                _fn(f), _cache(std::forward<T>(cache)) { }
            template <typename... A>
            auto operator() (A&&... args)const {
                auto cache2 = std::tuple_cat(_cache, std::forward_as_tuple(args...));
                return CurriedFunction<F, i - 1, decltype(cache2)>(_fn, std::move(cache2));
            }
        };
        // ��I = 1ʱ�����ѡ�����ƫ�ػ���ģ�����ʵ����
        template <typename F, typename T>
        class CurriedFunction<F, 1, T> {
        private:
            const F& _fn;
            T _cache;
        public:
            CurriedFunction(const F& f, T&& cache) :
                _fn(f), _cache(std::forward<T>(cache)) { }
            template <typename... A>
            auto operator() (A&&... args) {
                auto cache2 = std::tuple_cat(_cache, std::forward_as_tuple(args...));
                return std::apply(_fn, std::move(cache2));
            }
        };
    }
    template <std::size_t I = 2, typename FuncT>
    decltype(auto) curry(const FuncT& f) {
        return CurriedFunction<FuncT, I, std::tuple<>>(f, std::tuple<>());
    }
}