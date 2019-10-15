<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
require_once FW_PATH.'app/models/BaseModel.php';
/**
 * Description of MenuModel
 *
 * @author BB
 */
class MenuModel extends BaseModel {

    
    /**
     * @param String $controller
     * @return Array
     */
    public function getMenuItems($controller) 
    {
        $sql = "SELECT * FROM menu";
        $this->db->executeQuery($sql);
        
        
        while($row = $this->db->getRows()) {
            $items[$row['id']]['id'] = $row['id'];
            $items[$row['id']]['controller'] = $row['controller'];
            $items[$row['id']]['value'] = $row['value'];
            
            if ( $row['controller'] == $controller) {
                $items[$row['id']]['active'] = true;
            }
        }
        
        return (array) $items;
    }
}
