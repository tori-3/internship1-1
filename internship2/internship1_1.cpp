#include<iostream>
#include<string>
#include <fstream>
#include <sstream> 

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

        ListIterator(ListElement* ptr) :element{ptr}
        {

        }

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

    std::ifstream file;
    std::string line;

    file.open("Scores.txt", std::ios::in);

    //一行ずつ読み込む
    while (std::getline(file, line))
    {
        std::pair<int, std::string>data;

        //タブで区切り、リストに追加する。
        std::string temp;
        std::stringstream ss{ line };
        std::getline(ss, temp, '\t');
        data.first = atoi(temp.c_str());
        std::getline(ss, temp, '\t');
        data.second = temp;

        list.add(data);
    }

    for (const auto& data : list)
    {
        std::cout << data.first <<"\t" << data.second << std::endl;
    }
}
