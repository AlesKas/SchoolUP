<?php

namespace app\models;

class CarsModel extends BaseModel {
    
    
    public function getAllCars() 
    {
        $sql = "SELECT * FROM cars";
        $this->db->executeQuery($sql);
        $data = array();
        
        while($row = $this->db->getRows()) {
            $data[] = $row;
        }
        return $data;
    }
    
    
    /**
     * Vrátí uživatele podle jeho ID
     * @param int $id
     * @return array
     */
    public function getCarsById($id) 
    {
        $sql = "SELECT * "
                . "FROM cars "
                . "WHERE id = {$id}";
                
        $this->db->executeQuery($sql);
        return $this->db->getRows();
    }
    
    public function save($data) 
    {       
        unset($data['action']);
        $this->db->insertRecords('cars', $data);
    }
    

    public function delete($id) 
    {
        $cond = "id = ".$id;
        $this->db->deleteRecords('cars', $cond, 1);
    }
    
    public function update($id, $data) 
    {
        unset($data['action']);
        $cond = "id = ".$id;
        $this->db->updateRecords('cars', $data, $cond);
    }
}
