<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
require_once FW_PATH.'app/models/BaseModel.php';
/**
 * Description of PageModel
 *
 * @author Honza
 */
class UserModel extends BaseModel {
    
    
    /**
     * @return Array
     */
    public function getUsers()     
    {
        $sql = "SELECT * "
                . "FROM users";
        
        $this->db->executeQuery($sql);
        $data = array();
        
        while($row = $this->db->getRows()) {
            $data[] = $row;
        }
        return $data;
    }
    
    /**
     * @param Int $id
     * @return Array
     */
    public function getUserById($id) 
    {
        $sql = "SELECT * "
                . "FROM users "
                . "WHERE id = {$id}";
                
        $this->db->executeQuery($sql);
        return (array) $this->db->getRows();
    }
    
    
    /**
     * @param Array $senddata
     */
    public function save($senddata) 
    {
        $data['firstname'] = $senddata['firstname'];
        $data['lastname'] = $senddata['lastname'];
        $data['created'] = date('Y-m-d H:i:s');
        
        $this->db->insertRecords('users', $data);
    }
    
    
    /**
     * @param Int $id
     */
    public function delete($id) 
    {
        $cond = "id = ".$id;
        $this->db->deleteRecords('users', $cond, 1);
    }
    
    
    /** 
     * @param Int $id
     * @param Array $senddata
     */
    public function update($id, $senddata) 
    {
        $data['firstname'] = $senddata['firstname'];
        $data['lastname'] = $senddata['lastname']; 
        $cond = "id = ".$id;
        $this->db->updateRecords('users', $data, $cond);
    }
}
