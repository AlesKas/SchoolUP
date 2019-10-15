<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Db
 *
 * @author Honza
 */
class Db {

    /** @var Connection */ 
    private $connection;

    /** @var Int Count of Querys */ 
    private $queryCounter = 0;

    /** @var Result of Last Query */ 
    private $last;
	
    
    /**
     * Create New Connection With DB Server
     * @param String $host
     * @param String $user
     * @param String $password
     * @param String $database
     * @return Int
     */
    public function connection( $host, $user, $password, $database ) 
    {   	
        if (!$this->connection) {
            $this->connection = new \mysqli( $host, $user, $password, $database );
            mysqli_set_charset($this->connection, "utf8");

            if (mysqli_connect_errno()) {
                trigger_error('Chyba při připojování. '.$this->connection->error, E_USER_ERROR);
            } 
        }
    }   
    
    
    /**
     * Execute SQL 
     * @param SQL $queryStr
     * @return queryCounter++ 
     */
    public function executeQuery($queryStr) 
    {
    	if (!$result = $this->connection->query( $queryStr )) {
	    echo $queryStr;
            trigger_error('Chyba při provádění dotazu: '.$this->connection->error, E_USER_ERROR);
	}
	else {
            $this->last = $result;
            return $this->queryCounter++;
        }		
    }    
    
    
    /**
     * Return Rows number
     * @return Int
     */
    public function getNumRows() 
    {
        return $this->last->num_rows;                    
    }
    

    /**
     * Return Results From Query
     * @return Int
     */
    public function getRows()
    {
        return $this->last->fetch_array(MYSQLI_ASSOC);
   
    }

    
    /**
     * Remove data From Table
     * @param String $table
     * @param String $condition
     * @param Int $limit
     */
    public function deleteRecords($table, $condition, $limit) 
    {
    	$limits = ( $limit == '' ) ? '' : ' LIMIT ' . $limit;
    	$delete = "DELETE FROM {$table} WHERE {$condition} {$limits}";
    	$this->executeQuery( $delete );
    }
    

    /**
     * Update data in Table
     * @param String $table
     * @param Array $changes
     * @param String $condition
     * @return boolean
     */
    public function updateRecords($table, $changes, $condition) 
    {
    	$update = "UPDATE " . $table . " SET ";
    	foreach( $changes as $field => $value ) {
    		$update .= "`" . $field . "`='{$value}',";
    	}
    	   	
    	// remove last ','
    	$update = substr($update, 0, -1);
    	if ( $condition != '' ) {
            $update .= " WHERE " . $condition;
    	}	
    	$this->executeQuery( $update );    	
    	return true;    	
    }
    

    /**
     * Insert Data to Table
     * @param String $table
     * @param tArray $data
     * @return boolean
     */
    public function insertRecords($table, $data) 
    {
    	// setup some variables for fields and values
    	$fields  = "";
	$values = "";
		
        // sets attributes and values
        foreach ($data as $f => $v) {			
                 $fields .= "`$f`,";
                 $values .= ( is_numeric( $v ) && ( intval( $v ) == $v ) ) ? $v."," : "'$v',";		
        }
		
	// remove last ',' 
    	$setfields = substr($fields, 0, -1);
    	$setvalues = substr($values, 0, -1);
    	
        $insert = "INSERT INTO $table ({$setfields}) VALUES({$setvalues})";
        $this->executeQuery( $insert );
        return true;
    }
    

    /**
     * @return Int
     */
    public function getLastInsertID() 
    {
	return $this->connection->insert_id;
    }
    
    
    /**
     * Return Count Queries
     * @return Int
     */
    public function getQueryCount() 
    {
        return $this->queryCounter;
    }
    

    /**
     * @param String $data
     * @return Escaped data
     */
    public function sanitizeData($data) 
    {
    	return $this->connection->real_escape_string($data);
    }
    

    /**
     * Close Connection
     */
    public function __destruct() 
    {
        $this->connection->close();
    }
}
