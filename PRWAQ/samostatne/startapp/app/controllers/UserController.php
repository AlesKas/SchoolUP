<?php


namespace app\controllers;

use app\models\UserModel;
use phpboom\services\Register;

/**
 * Controller pomocí něhož řídíme správu uživatelů
 */
class UserController extends BaseController {
      
    
    /** @var UserModel */ 
    private $model;
    
    
    /**
     * @param Register $register
     */
    public function __construct(Register $register) 
    {
        parent::__construct($register);
        $this->model = new UserModel($this->register->getService('db'));
        $this->manageAction();
    }
    
    
    /**
     * Helper
     * Tato metoda podle akce v URL volá příslušné metody
     */
    public function manageAction() 
    {
        $action = $this->register->getService('Request')->getUrl('action');
        $id = $this->register->getService('Request')->getUrl('id');
              
        if ($action === 'add') {
            $this->actionAdd();
        }
        elseif ($action === 'edit') {
            $this->actionEdit($id);
        }
        elseif ($action === 'delete') {
            $this->actionDelete($id);
        }
        else {
            $this->actionDefault();
        }
    }
    
    
    public function actionDefault() 
    {
        $users = (array) $this->model->getAllUsers();
        $this->addToTemplate('users', $users);    
        $this->setTitle('Uživatelé');
        $this->render();
    }
    
    
    public function actionAdd() 
    {
        if ($this->register->getService('Request')->getPost('action')) {
            $this->model->save($this->register->getService('Request')->getPost());
            $this->redirect('user');
        }
        $this->addToTemplate('actionRender', 'Přidat');
        $this->setTitle('Přidat uživatele');
        $this->render();
    }
    
    
    /**
     * @param int $id
     */
    public function actionDelete($id) 
    {
        if (is_numeric($id)) {
            $this->model->delete($id);
        }
        $this->redirect('user');
    }
    
    
    /**
     * @param int $id
     */
    public function actionEdit($id) 
    {
        if (is_numeric($id) && $this->register->getService('Request')->getPost('action')) {
            $this->model->update($id, $this->register->getService('Request')->getPost());
            $this->redirect('user');
        } else {
            $this->setTitle('Editovat uživatele');
            $this->addToTemplate('actionRender', 'Editovat');
            $this->addToTemplate('data', $this->model->getUserById($id));
            $this->render();
        }         
    }

}