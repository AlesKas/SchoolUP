<?php

namespace app\models;

/**
 * Modelová třída, který obsluhuje databázovou tabulku users
 */
class UserModel extends BaseModel {
    
    
    /**
     * Vrátí všechny uživatale v poli
     * @return array
     */
    public function getAllUsers() 
    {
        $sql = "SELECT * FROM users";
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
    public function getUserById($id) 
    {
        $sql = "SELECT * "
                . "FROM users "
                . "WHERE id = {$id}";
                
        $this->db->executeQuery($sql);
        return $this->db->getRows();
    }
    
    
    /**
     * Uloží nového uživatele
     * @param array $data
     */
    public function save($data) 
    {       
        unset($data['action']);
        $this->db->insertRecords('users', $data);
    }
    
    
    /**
     * Odstraní uživatele
     * @param int $id
     */
    public function delete($id) 
    {
        $cond = "id = ".$id;
        $this->db->deleteRecords('users', $cond, 1);
    }
    
    
    /**
     * Upraví záznam uživatele v databázi
     * @param int $id
     * @param array $data
     */
    public function update($id, $data) 
    {
        unset($data['action']);
        $cond = "id = ".$id;
        $this->db->updateRecords('users', $data, $cond);
    }
}
