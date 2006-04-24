#include "../libplacian/discrete_model.cpp"
#include "../libplacian/fraction.cpp"
#include "../libplacian/iprobe.cpp"
#include "../libplacian/model.cpp"
#include "../libplacian/poly.cpp"

template class discrete_model<double>;
template class fraction<double>;
template class iprobe<double>;
template class model<double>;
template class polynomian<double>;

#include "../libplacian/discrete_borel.cpp"
