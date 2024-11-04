//
// Created by Eugene Bychkov on 20.10.2024.
//

#ifndef MINIMIZEROPTIMIZER_TASKF_H
#define MINIMIZEROPTIMIZER_TASKF_H
#include "Function.h"
#include "Matrix.h"
#include "Task.h"
class TaskF: public Task {
    Function* c_function;
    std::vector<Variable*> m_X;
    public:
    TaskF(Function*c_function, std::vector<Variable*> x): c_function(c_function), m_X(std::move(x)){}
    Matrix<> gradient() const override {
        Matrix<> gradient(m_X.size(), 1);
        for (int i = 0; i < m_X.size(); i++) {
            gradient(i, 0) = c_function->derivative(m_X[i])->evaluate();
        }
        return gradient;
    }
    Matrix<> hessian() const override{
        Matrix<> hessian(m_X.size(), m_X.size());
        for (int i = 0; i < m_X.size(); i++) {
            Function* f = c_function->derivative(m_X[i]);
            for (int j = 0; j < m_X.size(); j++) {
                hessian(i, j) = f->derivative(m_X[j])->evaluate();
            }
        }
        return hessian;
    }
    inline double getError() const override{
        return c_function->evaluate();
    }
    inline std::vector<double> getValues() const override{
        std::vector<double> values;
        for (auto & x : m_X) {
            values.push_back(x->evaluate());
        }
        return values;
    }
    double setError(std::vector<double> x) override{
        for (int i = 0; i < m_X.size(); i++) {
            m_X[i]->setValue(x[i]);
        }
        return c_function->evaluate();
    }
};
#endif //MINIMIZEROPTIMIZER_TASKF_H