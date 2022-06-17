#ifndef SORBET_TREEMAP_H
#define SORBET_TREEMAP_H

#include "ast/Trees.h"
#include "common/has_member.h"
#include "core/Context.h"
#include "core/GlobalState.h"
#include "core/errors/internal.h"
#include <memory>
#include <type_traits> // To use 'std::integral_constant'.
#include <typeinfo>

namespace sorbet::ast {

class FUNC_EXAMPLE {
public:
    // all members are optional, but METHOD NAMES MATTER
    // Not including the member will skip the branch
    // you may return the same pointer that you are given
    // caller is responsible to handle it
    ExpressionPtr preTransformClassDef(core::MutableContext ctx, ClassDef *original);
    ExpressionPtr postTransformClassDef(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformMethodDef(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformMethodDef(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformIf(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformIf(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformWhile(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformWhile(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformBreak(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformRetry(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformNext(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformReturn(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformReturn(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformRescueCase(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformRescueCase(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformRescue(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformRescue(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformUnresolvedIdent(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformAssign(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformAssign(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformSend(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformSend(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformHash(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformHash(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformArray(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postransformArray(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformConstantLit(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformUnresolvedConstantLit(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr postTransformRuntimeMethodDefinition(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformBlock(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformBlock(core::MutableContext ctx, ExpressionPtr original);

    ExpressionPtr preTransformInsSeq(core::MutableContext ctx, ExpressionPtr original);
    ExpressionPtr postTransformInsSeq(core::MutableContext ctx, ExpressionPtr original);
};

// NOTE: Implementations must use a context type parameter that `MutableContext` is convertable to.
// That is, either `Context` or `MutableContext`.
#define GENERATE_HAS_MEMBER_VISITOR(X, arg_types...)                               \
    GENERATE_HAS_MEMBER(X, arg_types)

// used to check for ABSENCE of method

#define GENERATE_POSTPONE_PRECLASS(X, arg_types...)                                  \
    GENERATE_CALL_MEMBER(preTransform##X, Exception::raise("should never be called. Incorrect use of TreeMap?"); \
                         return nullptr, arg_types)

#define GENERATE_POSTPONE_POSTCLASS(X, arg_types...)                                 \
    GENERATE_CALL_MEMBER(postTransform##X, Exception::raise("should never be called. Incorrect use of TreeMap?"); \
                         return nullptr, arg_types)


#define GENERATE_METAPROGRAMMING_FOR(arg_types...) \
GENERATE_HAS_MEMBER_VISITOR(preTransformUnresolvedIdent, arg_types); \
GENERATE_HAS_MEMBER_VISITOR(preTransformLocal, arg_types); \
GENERATE_HAS_MEMBER_VISITOR(preTransformUnresolvedConstantLit, arg_types); \
GENERATE_HAS_MEMBER_VISITOR(preTransformConstantLit, arg_types); \
GENERATE_HAS_MEMBER_VISITOR(preTransformLiteral, arg_types); \
GENERATE_HAS_MEMBER_VISITOR(preTransformRuntimeMethodDefinition, arg_types); \
 \
GENERATE_POSTPONE_PRECLASS(Expression, arg_types); \
GENERATE_POSTPONE_PRECLASS(ClassDef, arg_types); \
GENERATE_POSTPONE_PRECLASS(MethodDef, arg_types); \
GENERATE_POSTPONE_PRECLASS(If, arg_types); \
GENERATE_POSTPONE_PRECLASS(While, arg_types); \
GENERATE_POSTPONE_PRECLASS(Break, arg_types); \
GENERATE_POSTPONE_PRECLASS(Retry, arg_types); \
GENERATE_POSTPONE_PRECLASS(Next, arg_types); \
GENERATE_POSTPONE_PRECLASS(Return, arg_types); \
GENERATE_POSTPONE_PRECLASS(RescueCase, arg_types); \
GENERATE_POSTPONE_PRECLASS(Rescue, arg_types); \
GENERATE_POSTPONE_PRECLASS(Assign, arg_types); \
GENERATE_POSTPONE_PRECLASS(Send, arg_types); \
GENERATE_POSTPONE_PRECLASS(Hash, arg_types); \
GENERATE_POSTPONE_PRECLASS(Array, arg_types); \
GENERATE_POSTPONE_PRECLASS(Block, arg_types); \
GENERATE_POSTPONE_PRECLASS(InsSeq, arg_types); \
GENERATE_POSTPONE_PRECLASS(Cast, arg_types); \
\
GENERATE_POSTPONE_POSTCLASS(ClassDef, arg_types); \
GENERATE_POSTPONE_POSTCLASS(MethodDef, arg_types); \
GENERATE_POSTPONE_POSTCLASS(If, arg_types); \
GENERATE_POSTPONE_POSTCLASS(While, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Break, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Retry, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Next, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Return, arg_types); \
GENERATE_POSTPONE_POSTCLASS(RescueCase, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Rescue, arg_types); \
GENERATE_POSTPONE_POSTCLASS(UnresolvedIdent, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Assign, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Send, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Hash, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Array, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Local, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Literal, arg_types); \
GENERATE_POSTPONE_POSTCLASS(UnresolvedConstantLit, arg_types); \
GENERATE_POSTPONE_POSTCLASS(ConstantLit, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Block, arg_types); \
GENERATE_POSTPONE_POSTCLASS(InsSeq, arg_types); \
GENERATE_POSTPONE_POSTCLASS(Cast, arg_types); \
GENERATE_POSTPONE_POSTCLASS(RuntimeMethodDefinition, arg_types); \

struct MapFunctions {
    GENERATE_METAPROGRAMMING_FOR(std::declval<core::MutableContext>(), std::declval<ExpressionPtr>());
};

// Used to indicate that TreeMap has already reported location for this exception
struct ReportedRubyException {
    SorbetException reported;
    core::LocOffsets onLoc;
};

enum class TreeMapKind {
    Map,
};

enum class TreeMapDepthKind {
    Full,
    Shallow,
};

/**
 * Given a tree transformer FUNC transform a tree.
 * Tree is guaranteed to be visited in the definition order.
 * FUNC may maintain internal state.
 * @tparam tree transformer, see FUNC_EXAMPLE
 */
template <class FUNC, class CTX, TreeMapKind Kind, TreeMapDepthKind DepthKind> class TreeMapper {
private:
    friend class TreeMap;
    friend class ShallowMap;

    using Funcs = MapFunctions;

    FUNC &func;

    static_assert(!Funcs::HAS_MEMBER_preTransformUnresolvedIdent<FUNC>(), "use post*Transform instead");
    static_assert(!Funcs::HAS_MEMBER_preTransformLiteral<FUNC>(), "use post*Transform instead");
    static_assert(!Funcs::HAS_MEMBER_preTransformUnresolvedConstantLit<FUNC>(), "use post*Transform instead");
    static_assert(!Funcs::HAS_MEMBER_preTransformConstantLit<FUNC>(), "use post*Transform instead");
    static_assert(!Funcs::HAS_MEMBER_preTransformLocal<FUNC>(), "use post*Transform instead");
    static_assert(!Funcs::HAS_MEMBER_preTransformRuntimeMethodDefinition<FUNC>(), "use post*Transform instead");

    TreeMapper(FUNC &func) : func(func) {}

    ExpressionPtr mapClassDef(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformClassDef<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformClassDef<FUNC>::call(func, ctx, std::move(v));
        }

        // We intentionally do not walk v->ancestors nor v->singletonAncestors.
        //
        // These lists used to be guaranteed to be simple trees (only constant literals) by desugar,
        // but that was later relaxed. In places where walking ancestors is required, instead define
        // your `preTransformClassDef` method to contain this:
        //
        //   for (auto &ancestor : klass.ancestors) {
        //       ancestor = ast::TreeMap::apply(ctx, *this, std::move(ancestor))
        //   }
        //
        // and that will have the same effect, without having to retroactively change all TreeMaps.

        for (auto &def : cast_tree_nonnull<ClassDef>(v).rhs) {
            def = mapIt(std::move(def), ctx.withOwner(cast_tree_nonnull<ClassDef>(v).symbol).withFile(ctx.file));
        }

        if constexpr (Funcs::HAS_MEMBER_postTransformClassDef<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformClassDef<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapMethodDef(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformMethodDef<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformMethodDef<FUNC>::call(func, ctx, std::move(v));
        }

        for (auto &arg : cast_tree_nonnull<MethodDef>(v).args) {
            // Only OptionalArgs have subexpressions within them.
            if (auto *optArg = cast_tree<OptionalArg>(arg)) {
                optArg->default_ =
                    mapIt(std::move(optArg->default_), ctx.withOwner(cast_tree_nonnull<MethodDef>(v).symbol));
            }
        }

        if constexpr (DepthKind == TreeMapDepthKind::Full) {
            cast_tree_nonnull<MethodDef>(v).rhs =
                mapIt(std::move(cast_tree_nonnull<MethodDef>(v).rhs),
                      ctx.withOwner(cast_tree_nonnull<MethodDef>(v).symbol).withFile(ctx.file));
        }

        if constexpr (Funcs::HAS_MEMBER_postTransformMethodDef<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformMethodDef<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapIf(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformIf<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformIf<FUNC>::call(func, ctx, std::move(v));
        }
        cast_tree_nonnull<If>(v).cond = mapIt(std::move(cast_tree_nonnull<If>(v).cond), ctx);
        cast_tree_nonnull<If>(v).thenp = mapIt(std::move(cast_tree_nonnull<If>(v).thenp), ctx);
        cast_tree_nonnull<If>(v).elsep = mapIt(std::move(cast_tree_nonnull<If>(v).elsep), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformIf<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformIf<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapWhile(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformWhile<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformWhile<FUNC>::call(func, ctx, std::move(v));
        }
        cast_tree_nonnull<While>(v).cond = mapIt(std::move(cast_tree_nonnull<While>(v).cond), ctx);
        cast_tree_nonnull<While>(v).body = mapIt(std::move(cast_tree_nonnull<While>(v).body), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformWhile<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformWhile<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapBreak(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformBreak<FUNC>()) {
            return Funcs::CALL_MEMBER_preTransformBreak<FUNC>::call(func, ctx, std::move(v));
        }

        cast_tree_nonnull<Break>(v).expr = mapIt(std::move(cast_tree_nonnull<Break>(v).expr), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformBreak<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformBreak<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }
    ExpressionPtr mapRetry(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformRetry<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformRetry<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapNext(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformNext<FUNC>()) {
            return Funcs::CALL_MEMBER_preTransformNext<FUNC>::call(func, ctx, std::move(v));
        }

        cast_tree_nonnull<Next>(v).expr = mapIt(std::move(cast_tree_nonnull<Next>(v).expr), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformNext<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformNext<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapReturn(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformReturn<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformReturn<FUNC>::call(func, ctx, std::move(v));
        }
        cast_tree_nonnull<Return>(v).expr = mapIt(std::move(cast_tree_nonnull<Return>(v).expr), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformReturn<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformReturn<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapRescueCase(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformRescueCase<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformRescueCase<FUNC>::call(func, ctx, std::move(v));
        }

        for (auto &el : cast_tree_nonnull<RescueCase>(v).exceptions) {
            el = mapIt(std::move(el), ctx);
        }

        cast_tree_nonnull<RescueCase>(v).var = mapIt(std::move(cast_tree_nonnull<RescueCase>(v).var), ctx);

        cast_tree_nonnull<RescueCase>(v).body = mapIt(std::move(cast_tree_nonnull<RescueCase>(v).body), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformRescueCase<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformRescueCase<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }
    ExpressionPtr mapRescue(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformRescue<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformRescue<FUNC>::call(func, ctx, std::move(v));
        }

        cast_tree_nonnull<Rescue>(v).body = mapIt(std::move(cast_tree_nonnull<Rescue>(v).body), ctx);

        for (auto &el : cast_tree_nonnull<Rescue>(v).rescueCases) {
            ENFORCE(isa_tree<RescueCase>(el), "invalid tree where rescue case was expected");
            el = mapRescueCase(std::move(el), ctx);
            ENFORCE(isa_tree<RescueCase>(el), "rescue case was mapped into non-rescue case");
        }

        cast_tree_nonnull<Rescue>(v).else_ = mapIt(std::move(cast_tree_nonnull<Rescue>(v).else_), ctx);
        cast_tree_nonnull<Rescue>(v).ensure = mapIt(std::move(cast_tree_nonnull<Rescue>(v).ensure), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformRescue<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformRescue<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapUnresolvedIdent(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformUnresolvedIdent<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformUnresolvedIdent<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapAssign(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformAssign<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformAssign<FUNC>::call(func, ctx, std::move(v));
        }

        cast_tree_nonnull<Assign>(v).lhs = mapIt(std::move(cast_tree_nonnull<Assign>(v).lhs), ctx);
        cast_tree_nonnull<Assign>(v).rhs = mapIt(std::move(cast_tree_nonnull<Assign>(v).rhs), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformAssign<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformAssign<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapSend(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformSend<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformSend<FUNC>::call(func, ctx, std::move(v));
        }

        cast_tree_nonnull<Send>(v).recv = mapIt(std::move(cast_tree_nonnull<Send>(v).recv), ctx);

        for (auto &arg : cast_tree_nonnull<Send>(v).nonBlockArgs()) {
            arg = mapIt(std::move(arg), ctx);
            ENFORCE(arg != nullptr);
        }

        if (auto *block = cast_tree_nonnull<Send>(v).rawBlock()) {
            *block = mapIt(std::move(*block), ctx);
            ENFORCE(cast_tree_nonnull<Send>(v).block() != nullptr, "block was mapped into not-a block");
        }

        if constexpr (Funcs::HAS_MEMBER_postTransformSend<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformSend<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapHash(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformHash<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformHash<FUNC>::call(func, ctx, std::move(v));
        }
        for (auto &key : cast_tree_nonnull<Hash>(v).keys) {
            key = mapIt(std::move(key), ctx);
        }

        for (auto &value : cast_tree_nonnull<Hash>(v).values) {
            value = mapIt(std::move(value), ctx);
        }

        if constexpr (Funcs::HAS_MEMBER_postTransformArray<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformHash<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapArray(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformArray<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformArray<FUNC>::call(func, ctx, std::move(v));
        }
        for (auto &elem : cast_tree_nonnull<Array>(v).elems) {
            elem = mapIt(std::move(elem), ctx);
        }

        if constexpr (Funcs::HAS_MEMBER_postTransformArray<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformArray<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapLiteral(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformLiteral<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformLiteral<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapUnresolvedConstantLit(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformUnresolvedConstantLit<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformUnresolvedConstantLit<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapConstantLit(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformConstantLit<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformConstantLit<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapBlock(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformBlock<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformBlock<FUNC>::call(func, ctx, std::move(v));
        }

        for (auto &arg : cast_tree_nonnull<Block>(v).args) {
            // Only OptionalArgs have subexpressions within them.
            if (auto *optArg = cast_tree<OptionalArg>(arg)) {
                optArg->default_ = mapIt(std::move(optArg->default_), ctx);
            }
        }
        cast_tree_nonnull<Block>(v).body = mapIt(std::move(cast_tree_nonnull<Block>(v).body), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformBlock<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformBlock<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapInsSeq(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformInsSeq<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformInsSeq<FUNC>::call(func, ctx, std::move(v));
        }

        for (auto &stat : cast_tree_nonnull<InsSeq>(v).stats) {
            stat = mapIt(std::move(stat), ctx);
        }

        cast_tree_nonnull<InsSeq>(v).expr = mapIt(std::move(cast_tree_nonnull<InsSeq>(v).expr), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformInsSeq<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformInsSeq<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapLocal(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformLocal<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformLocal<FUNC>::call(func, ctx, std::move(v));
        }
        return v;
    }

    ExpressionPtr mapCast(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_preTransformCast<FUNC>()) {
            v = Funcs::CALL_MEMBER_preTransformCast<FUNC>::call(func, ctx, std::move(v));
        }
        cast_tree_nonnull<Cast>(v).arg = mapIt(std::move(cast_tree_nonnull<Cast>(v).arg), ctx);

        if constexpr (Funcs::HAS_MEMBER_postTransformCast<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformCast<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapRuntimeMethodDefinition(ExpressionPtr v, CTX ctx) {
        if constexpr (Funcs::HAS_MEMBER_postTransformRuntimeMethodDefinition<FUNC>()) {
            return Funcs::CALL_MEMBER_postTransformRuntimeMethodDefinition<FUNC>::call(func, ctx, std::move(v));
        }

        return v;
    }

    ExpressionPtr mapIt(ExpressionPtr what, CTX ctx) {
        if (what == nullptr) {
            return what;
        }
        auto loc = what.loc();

        try {
            // TODO: reorder by frequency
            if constexpr (Funcs::HAS_MEMBER_preTransformExpression<FUNC>()) {
                what = Funcs::CALL_MEMBER_preTransformExpression<FUNC>::call(func, ctx, std::move(what));
            }

            switch (what.tag()) {
                case Tag::EmptyTree:
                    return what;

                case Tag::Send:
                    return mapSend(std::move(what), ctx);

                case Tag::ClassDef:
                    return mapClassDef(std::move(what), ctx);

                case Tag::MethodDef:
                    return mapMethodDef(std::move(what), ctx);

                case Tag::If:
                    return mapIf(std::move(what), ctx);

                case Tag::While:
                    return mapWhile(std::move(what), ctx);

                case Tag::Break:
                    return mapBreak(std::move(what), ctx);

                case Tag::Retry:
                    return mapRetry(std::move(what), ctx);

                case Tag::Next:
                    return mapNext(std::move(what), ctx);

                case Tag::Return:
                    return mapReturn(std::move(what), ctx);

                case Tag::RescueCase:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::Rescue:
                    return mapRescue(std::move(what), ctx);

                case Tag::Local:
                    return mapLocal(std::move(what), ctx);

                case Tag::UnresolvedIdent:
                    return mapUnresolvedIdent(std::move(what), ctx);

                case Tag::RestArg:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::KeywordArg:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::OptionalArg:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::BlockArg:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::ShadowArg:
                    Exception::raise("should never happen. Forgot to add new tree kind? {}", what.nodeName());
                    break;

                case Tag::Assign:
                    return mapAssign(std::move(what), ctx);

                case Tag::Cast:
                    return mapCast(std::move(what), ctx);

                case Tag::Hash:
                    return mapHash(std::move(what), ctx);

                case Tag::Array:
                    return mapArray(std::move(what), ctx);

                case Tag::Literal:
                    return mapLiteral(std::move(what), ctx);

                case Tag::UnresolvedConstantLit:
                    return mapUnresolvedConstantLit(std::move(what), ctx);

                case Tag::ConstantLit:
                    return mapConstantLit(std::move(what), ctx);

                case Tag::ZSuperArgs:
                    return what;

                case Tag::Block:
                    return mapBlock(std::move(what), ctx);

                case Tag::InsSeq:
                    return mapInsSeq(std::move(what), ctx);

                case Tag::RuntimeMethodDefinition:
                    return mapRuntimeMethodDefinition(std::move(what), ctx);
            }
        } catch (SorbetException &e) {
            Exception::failInFuzzer();

            throw ReportedRubyException{e, loc};
        }
    }
};

class TreeMap {
public:
    template <typename CTX, typename FUNC> static ExpressionPtr apply(CTX ctx, FUNC &func, ExpressionPtr to) {
        TreeMapper<FUNC, CTX, TreeMapKind::Map, TreeMapDepthKind::Full> walker(func);
        try {
            return walker.mapIt(std::move(to), ctx);
        } catch (ReportedRubyException &exception) {
            Exception::failInFuzzer();
            if (auto e = ctx.beginError(exception.onLoc, core::errors::Internal::InternalError)) {
                e.setHeader("Failed to process tree (backtrace is above)");
            }
            throw exception.reported;
        }
    }
};

class ShallowMap {
public:
    template <typename CTX, typename FUNC> static ExpressionPtr apply(CTX ctx, FUNC &func, ExpressionPtr to) {
        TreeMapper<FUNC, CTX, TreeMapKind::Map, TreeMapDepthKind::Shallow> walker(func);
        try {
            return walker.mapIt(std::move(to), ctx);
        } catch (ReportedRubyException &exception) {
            Exception::failInFuzzer();
            if (auto e = ctx.beginError(exception.onLoc, core::errors::Internal::InternalError)) {
                e.setHeader("Failed to process tree (backtrace is above)");
            }
            throw exception.reported;
        }
    }
};

} // namespace sorbet::ast
#endif // SORBET_TREEMAP_H
