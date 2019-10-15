<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
require_once FW_PATH.'app/controllers/BaseController.php';
require_once FW_PATH.'app/models/UserModel.php';
/**
 * Description of PageController
 *
 * @author BB
 */
class UserController extends BaseController {
    
    
    private $model;
    
    
    public function __construct(Registr $registr) 
    {
        parent::__construct($registr);
        
        $this->model = new UserModel($registr->Db);
        
        $this->manageAction();    
    }
    
    
    private function manageAction() 
    {
        $action = $this->registr->Request->getUrl('action');
        $id = $this->registr->Request->getUrl('id');
        
        
        if ($action == 'add') {
            $this->actionAdd();
        }
        elseif ($action == 'edit') {
            $this->actionEdit($id);
        }
        elseif ($action == 'delete') {
            $this->actionDelete($id);
        }
        else {
            $this->renderDefault();
        }
    }
    
    
    private function actionAdd() 
    {
        //var_dump($this->registr->getService('Request')->getPost('action'));

        if ($this->registr->Request->getPost('useraction')) {
            $this->model->save($this->registr->Request->getPost());
            $this->redirect('user');
        }
        $this->renderAdd();
    }
    
    
    /**
     * @param Int $id
     */
    private function actionDelete($id) 
    {
        if (is_numeric($id)) {
            $this->model->delete($id);
        }
        $this->redirect('user');
    }
    
    
    /**
     * @param Int $id
     */
    private function actionEdit($id) 
    {
        if (is_numeric($id) && $this->registr->Request->getPost('useraction')) {
            $this->model->update($id, $this->registr->Request->getPost());
            $this->redirect('user');
        }
        else {
            $this->renderEdit($id);
        }              
    }
    
      
    
    public function renderDefault() 
    {
        $this->setTitle('Správa uživatelů');        
        $users = $this->model->getUsers();       
        require_once FW_PATH.'app/views/User/default.php';
    }
    
    
    public function renderAdd() 
    {
        $this->setTitle('Přidat uživatele');
        $actionRender = "Přidat";
        require_once FW_PATH.'app/views/User/add.php';
    }

    /**
     * @param Int $id
     */
    public function renderEdit($id) 
    {
        $this->setTitle('Editovat uživatele');
        $userData = $this->model->getUserById($id);
        $actionRender = "Editovat";
        require_once FW_PATH.'app/views/User/edit.php';        
    }
}
