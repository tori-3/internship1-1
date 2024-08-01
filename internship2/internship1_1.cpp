#include<iostream>
#include<string>

//双方向リスト
template <typename T>
class List
{
private:

    //リストの各要素
    struct ListElement
    {
        T data;

        ListElement* front = nullptr;

        ListElement* back = nullptr;
    };

    //リストのイテレーター(範囲forを使うため)
    class ListIterator
    {
    public:

        T& operator *()
        {
            return element->data;
        }

        void operator ++()
        {
            element = element->back;
        }

        bool operator !=(ListIterator& right)
        {
            return element != right.element;
        }
    private:
        ListElement* element;
    };

public:

    ListElement* begin_ptr = nullptr;
    ListElement* end_ptr = nullptr;

    //beginのイテレーターを返す
    ListIterator begin() const
    {
        return ListIterator{ begin_ptr };
    }

    //endのイテレーターを返す
    ListIterator end() const
    {
        return ListIterator{ nullptr };
    }

    //後ろに要素を追加する
    void add(const T& addData)
    {

        if (begin_ptr == nullptr)
        {
            begin_ptr = new ListElement{ addData,nullptr,nullptr };
            end_ptr = begin_ptr;
        }
        else 
        {
            end_ptr->back = new ListElement{ addData,end_ptr,nullptr };
            end_ptr->back->front = end_ptr;
            end_ptr = end_ptr->back;
        }
    }
};

int main() 
{
    //テストコード
    List<std::pair<int,std::string>> list;

    list.add({ 10,"aaaa" });
    list.add({ 20,"bbbb" });
    list.add({ 30,"cccc" });
    list.add({ 40,"dddd" });

    for (const auto& data : list)
    {
        std::cout << data.first << data.second<<std::endl;
    }

}
