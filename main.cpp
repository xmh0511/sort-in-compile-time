#include <iostream>
#include <array>
template<class T, T...number>
struct Set{};
template<std::size_t...N>
constexpr auto construct_std_array(){

}
template<class T, T...number>
constexpr std::array<T, sizeof...(number)> sort_help(Set<T, number...>){
    T arr[] = {number...};
    const auto size =  sizeof...(number);
    for(auto i = 0;i< size - 1; i++){
        for(auto j = 0; j< size - 1 - i;j++){
            if(arr[j] > arr[j+1]){
                auto tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    std::array<T,sizeof...(number)> ret;
    for(auto i = 0; i< size;i++){
        ret[i] = arr[i];
    }
    return ret;
}
template<class T ,T ... number, std::size_t... Index>
constexpr auto construct_set(Set<T, number...> v, std::index_sequence<Index...>){
    constexpr auto arr = sort_help(v);
    return Set<T, arr[Index]...>{};
}
template<class T, T...number>
constexpr auto sort(Set<T, number...> v){
    return construct_set(v,std::make_index_sequence<sizeof...(number)>());
}
int main(){
   constexpr auto v = sort(Set<int,5,2,1,3>{});
   std::cout<< typeid(v).name();
}
