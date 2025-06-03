#pragma once
#include "AI.h"
#include <string>
namespace Game2048
{
    namespace Game
    {
        namespace TMP
        {
            // TMP, 启动！
            template <AIType T>
            struct AITypeSelector
            {
                using type = AIBase;
            };
            template <>
            struct AITypeSelector<AIType::CORNER>
            {
                using type = CornerAI;
            };
            template <>
            struct AITypeSelector<AIType::SWING>
            {
                using type = SwingAI;
            };
            template <>
            struct AITypeSelector<AIType::SWIRL>
            {
                using type = SwirlAI;
            };
            template <>
            struct AITypeSelector<AIType::RANDOM>
            {
                using type = RandomAI;
            };
            template <AIType T>
            using AITypeOf = typename TMP::AITypeSelector<T>::type;
            template <class T>
            struct _NameOf
            {
                constexpr static const char *value = "Unknown AI";
            };
            template <>
            struct _NameOf<RandomAI>
            {
                constexpr static const char *value = "Random AI";
            };
            template <>
            struct _NameOf<CornerAI>
            {
                constexpr static const char *value = "Corner AI";
            };
            template <>
            struct _NameOf<SwingAI>
            {
                constexpr static const char *value = "Swing AI";
            };
            template <>
            struct _NameOf<SwirlAI>
            {
                constexpr static const char *value = "Swirl AI";
            };
            template <class T>
            constexpr const char *NameOf = _NameOf<T>::value;
            template <int _Cnt>
            struct _AILister
            {
                static const char *value()
                {
                    static const std::string _res =
                        std::string(_AILister<_Cnt - 1>::value()) +
                        std::to_string(_Cnt) + ". " +
                        NameOf<AITypeOf<static_cast<AIType>(_Cnt - 1)>> + "\n";
                    return _res.c_str();
                }
            };
            template <>
            struct _AILister<0>
            {
                static const char *value()
                {
                    return "";
                }
            };
        }
        using TMP::AITypeOf;
        using TMP::NameOf;
        inline constexpr const int AICount = static_cast<int>(AIType::_ecAIType_Cnt);
        inline const char *AIList = TMP::_AILister<AICount>::value();
    }
}