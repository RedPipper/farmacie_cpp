#include "repository.h"

physical repository::find(int pos){
    return list.begin() + pos;
}

repository::repository():nrElems{0}{}

void repository::addElem(entity to_add){
    to_add.setCode(nrElems*1000 + (rand() % 100) );
    list.push_back(to_add);
    ++nrElems;
}

void repository::removeElem(int pos){

    physical location = find(pos);
    list.erase(location);
    --nrElems;
}

void repository::changeElement(int pos, entity updated){
    physical location = find(pos);
    
    if(updated.getName() != "")
        location->setName(updated.getName());
        
    if(updated.getPrice() != -1)
        location->setPrice(updated.getPrice());
    
    if(updated.getManufacturer() != "")
        location->setManufacturer(updated.getManufacturer());
    
    if(updated.getSubstance() != "")
        location->setSubstance(updated.getSubstance());

}

iter_pair repository::getAll(){
    return iter_pair(list.begin(),list.end());
}

int repository::getNrElems(){
    return nrElems;
}

entity repository::getElem(int pos){
    return *(find(pos));
}
void repository::DESTROY(){
    list.clear();
}

bool comparator_nume(entity a, entity b){
    if(a.getName() == b.getName())
        return a.getPrice() < b.getPrice();
    
    return a.getName() < b.getName();
}

bool comparator_manufacturer(entity a, entity b){
    if(a.getManufacturer() == b.getManufacturer())
        return a.getPrice() < b.getPrice();
    
    return a.getManufacturer() < b.getManufacturer();
}

bool comparator_substance(entity a, entity b){
    if(a.getSubstance() == b.getSubstance())
        return a.getPrice() < b.getPrice();
    
    return a.getSubstance() < b.getSubstance();
}


void repository::sortElems(int clause){
    switch(clause){
        case 0:
            sort(list.begin(),list.end(), comparator_nume);
            break;
        case 1:
            sort(list.begin(),list.end(), comparator_manufacturer);
            break;
        
        case 2:
            sort(list.begin(),list.end(), comparator_substance);
            break;            
    }
}


void repository_report::addItem(string manufacturer){

    auto search = reports.find(manufacturer); 

    if(search == reports.end() ){
        reports.insert(pair<string, int>(manufacturer, 1));
    }else{
        reports[manufacturer]++;
    }

}

int repository_report::getItem(string manufacturer) const{
    
    auto search = reports.find(manufacturer);

    if( search == reports.end())
        return -1;
    else
        return search->second;

}

void repository_report::removeItem(string manufacturer){
    auto search = reports.find(manufacturer);

    if(search == reports.end())
        throw range_error("Elementul nu exista in rapoarte.");
    else{
        --reports[manufacturer];

        if(reports[manufacturer] == 0)
            reports.erase(manufacturer);
    }
}

pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator>
repository_report::getAll(){
    return pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator>(reports.begin(), reports.end());
}