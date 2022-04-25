#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class page
{
private:
    vector<int> records;

public:
    // page();
    //~page();

    void insert_record(int a)
    {
        records.push_back(a);
    }
    vector<int> return_records()
    {
        return records;
    }
    void sort_page()
    {
        sort(records.begin(), records.end());
    }
    void change_records(vector<int> vec_temp)
    {
        records = vec_temp;
    }
};

class file
{
private:
    vector<page *> pages;
    int no_pages;
    int no_records;

public:
    file(int NO_PAGES, int NO_RECORDS)
    {
        no_pages = NO_PAGES;
        no_records = NO_RECORDS;
    }

    void insert_page(page *a)
    {
        pages.push_back(a);
    }

    void insert_at_index(int index, page *a)
    {
        pages.insert(pages.begin() + index, a);
    }

    void erase_at_index(int index)
    {
        pages.erase(pages.begin() + index);
    }

    page *return_page(int i) // returns page pointer
    {
        return pages[i];
    }
    vector<page *> return_pages_vec()
    {
        return pages;
    }
};

void print_page(page *pg)
{
    vector<int> temp = pg->return_records();
    for (int i = 0; i < temp.size(); i++)
    {
        cout << temp[i] << " ";
    }
    cout << endl;
}

void sort_page(page *pg)
{ // sorts page
    pg->sort_page();
}

int main()
{

    int buffer_pages;
    int records_p_page;
    int total_records;
    cin >> buffer_pages;
    cin >> records_p_page;
    cin >> total_records;
    int total_pages;
    if (total_records % records_p_page == 0)
    {
        total_pages = total_records / records_p_page;
    }
    else
    {
        total_pages = (total_records / records_p_page) + 1;
    }
    file fl(total_pages, total_records);

    int breaker = total_records;

    // pass0 iterator

    // input
    for (int i = 0; i < total_pages; i++) // creares and stores all pages
    {
        page *temp = new page();                 // creates a new page
        for (int j = 0; j < records_p_page; j++) // creates a new page and stores all the records in the page
        {
            if (breaker == 0)
            { // just checks if the last page has reached all the records
                break;
            }
            int n;
            cin >> n;
            temp->insert_record(n);
            breaker--; // to keep tally of all the records being inserted works kind of as a while loop
        }
        fl.insert_page(temp);
    }

    // merging every page to start the merging sort process

    // pass0
    for (int i = 0; i < total_pages; i++) // sorts all the pages in the beginning
    {
        sort_page(fl.return_page(i));
    }

    int no_runs_pass0;
    if (total_pages % buffer_pages == 0)
    {
        no_runs_pass0 = total_pages / buffer_pages;
    }
    else
    {
        no_runs_pass0 = (total_pages / buffer_pages) + 1;
    }

    for (int i = 0; i < no_runs_pass0; i++) // runs created at pass 0
    {

        for (int j = 0; j < buffer_pages - 1; j++) // runs and merges B - 1 times to get a run at that i value
        {
            vector<int> op1 = fl.return_page(i)->return_records();
            vector<int> op2 = fl.return_page(i + 1)->return_records();
            vector<int> result(op1.size() + op2.size());

            merge(op1.begin(), op1.end(), op2.begin(), op2.end(), result.begin());
            page *temp_page = new page();
            temp_page->change_records(result);
            // we have a new page that has result the sorted merged array as the new records
            fl.erase_at_index(i); // erased the other two pages
            fl.erase_at_index(i);
            // we inserted the new page which was merged from the previous two
            fl.insert_at_index(i, temp_page);
        }
    }

    // for (int i = 0; i < fl.return_pages_vec().size(); i++)//prints all the pages present DEBUG
    //{
    //     print_page(fl.return_page(i));
    // }

    // pass0 completes here
    // PASS0 running fine

    while (fl.return_pages_vec().size() > 1)
    {

        vector<int> op1 = fl.return_page(0)->return_records();
        vector<int> op2 = fl.return_page(1)->return_records();
        vector<int> result(op1.size() + op2.size());

        merge(op1.begin(), op1.end(), op2.begin(), op2.end(), result.begin());
        page *temp_page = new page();
        temp_page->change_records(result);
        // we have a new page that has result the sorted merged array as the new records
        fl.erase_at_index(0); // erased the other two pages
        fl.erase_at_index(0);
        // we inserted the new page which was merged from the previous two
        fl.insert_at_index(0, temp_page);
    }

    for (int i = 0; i < fl.return_pages_vec().size(); i++) // prints all the pages present DEBUG
    {
        print_page(fl.return_page(i));
    }

    return 0;
}
