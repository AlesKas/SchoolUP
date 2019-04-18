(defclass vehicle ()
  ((load-semaphore :initform (make-semaphore 1))
   (unload-semaphore :initform (make-semaphore 1))
   (count :initform 0)
   (capacity :initform 5)
   (passanger-count :initform 0)
   (sync-param :initform (make-semaphore 1))))

(defmethod get-load-semaphore ((vehicle vehicle))
  (slot-value vehicle 'load-semaphore))

(defmethod set-load-semaphore ((vehicle vehicle) value)
  (setf (slot-value vehicle 'load-semaphore) value))

(defmethod get-unload-semaphore ((vehicle vehicle))
  (slot-value vehicle 'unload-semaphore))

(defmethod set-unload-semaphore ((vehicle vehicle) value)
  (setf (slot-value vehicle 'unload-semaphore) value))

(defmethod get-travel-semaphore ((vehicle vehicle))
  (slot-value vehicle 'travel-semaphore))

(defmethod set-travel-semaphore ((vehicle vehicle) value)
  (setf (slot-value vehicle 'travel-semaphore) value))

(defmethod get-sync-param ((vehicle vehicle))
  (slot-value vehicle 'sync-param))

(defmethod set-sync-param ((vehicle vehicle) value)
  (setf (slot-value vehicle 'sync-param) value))

(defmethod get-passanger-count ((vehicle vehicle))
  (slot-value vehicle 'passanger-count))

(defmethod set-passanger-count ((vehicle vehicle) value)
  (setf (slot-value vehicle 'passanger-count) value))


(defmethod dec-passanger-count ((vehicle vehicle))
  (set-passanger-count vehicle 
                      (- (get-passanger-count vehicle)
                         (get-capacity vehicle))))

(defmethod inc-count ((vehicle vehicle))
  (setf (slot-value vehicle 'count) (+ 1 (slot-value vehicle 'count))))

(defmethod get-count ((vehicle vehicle))
  (slot-value vehicle 'count))

(defmethod set-zero ((vehicle vehicle))
  (setf (slot-value vehicle 'count) 0))

(defmethod dec-count ((vehicle vehicle))
  (setf (slot-value vehicle 'count) (- (slot-value vehicle 'count) 1)))

(defmethod get-capacity ((vehicle vehicle))
  (slot-value vehicle 'capacity))

(defmethod synch-print ((vehicle vehicle) text)
  (sem-wait (get-sync-param vehicle))
  (print text)
  (sem-signal (get-sync-param vehicle)))


(defmethod chuchu ((vehicle vehicle) passanger-count)
  (unless (> passanger-count (get-capacity vehicle))
    (error "Not enought passangers!"))
  (set-load-semaphore vehicle (make-semaphore (get-capacity vehicle)))
  (sem-signal (get-unload-semaphore vehicle))
  (sem-wait (get-unload-semaphore vehicle))
  (set-passanger-count vehicle  passanger-count)
  (dotimes (i passanger-count)
             (a-progn
               (progn
                 (let ((person (make-instance 'person)))
                   (board person vehicle)  
                   (if (check-capacity vehicle)
                       (progn 
                         (run-p vehicle)
                         (unboard person vehicle)
                         (unload-p vehicle))
                     (synch-print vehicle "Not enought passangers for next ride.")))))))

(defmethod load-p ((vehicle vehicle))
  (print "person leaves and let another group")
  (set-zero vehicle)
  (dotimes (i (get-capacity vehicle))
    (sem-signal (get-load-semaphore vehicle))))

(defmethod run-p ((vehicle vehicle))
  (sem-wait (get-sync-param vehicle))
  (inc-count vehicle)
  (if (= (get-count vehicle) (get-capacity vehicle))
      (progn
        (print "we are going")
        (sleep 3)
        (sem-signal (get-unload-semaphore vehicle))))
  (sem-signal (get-sync-param vehicle)))

(defmethod unload-p ((vehicle vehicle))
  (sem-wait (get-sync-param vehicle))
  (dec-count vehicle)
  (if (= (get-count vehicle) 1)
      (progn
        (dec-passanger-count vehicle)
        (load-p vehicle))
    (progn
      (sem-signal (get-unload-semaphore vehicle))))                 
  (sem-signal (get-sync-param vehicle)))

(defmethod check-capacity ((vehicle vehicle))
  (let ((is-ok NIL))
    (sem-wait (get-sync-param vehicle))
    (if (<= (get-capacity vehicle) (get-passanger-count vehicle))
        (setf is-ok t))
    (sem-signal (get-sync-param vehicle))
    is-ok))
                                 
  
(defclass person ()
  ())

(defmethod board ((person person) vehicle)
  (sem-wait (get-load-semaphore vehicle))
  (synch-print vehicle "person enters"))

(defmethod unboard ((person person) vehicle)
  (sem-wait (get-unload-semaphore vehicle))
   (synch-print vehicle "person leaves"))

