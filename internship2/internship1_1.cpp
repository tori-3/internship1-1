#include<iostream>
#include<string>

//�o�������X�g
template <typename T>
class List
{
private:

    //���X�g�̊e�v�f
    struct ListElement
    {
        T data;

        ListElement* front = nullptr;

        ListElement* back = nullptr;
    };

    //���X�g�̃C�e���[�^�[(�͈�for���g������)
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

    //begin�̃C�e���[�^�[��Ԃ�
    ListIterator begin() const
    {
        return ListIterator{ begin_ptr };
    }

    //end�̃C�e���[�^�[��Ԃ�
    ListIterator end() const
    {
        return ListIterator{ nullptr };
    }

    //���ɗv�f��ǉ�����
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
    //�e�X�g�R�[�h
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
