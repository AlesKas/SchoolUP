(defclass train ()
  ((load-sem :initform (make-semaphore 1))
   (unload-sem :initform (make-semaphore 1))
   (sync-sem :initform (make-semaphore 1))
   (count :initform 0)
   (capacity :initform 5)
   (passanger-count :initform 0)))

(defmethod get-load-sem ((train train))
  (slot-value train 'load-sem))

(defmethod set-load-sem ((train train) value)
  (setf (slot-value train 'load-sem) value))

(defmethod get-unload-sem ((train train))
  (slot-value train 'unload-sem))

(defmethod set-unload-sem ((train train) value)
  (setf (slot-value train 'unload-sem) value))

(defmethod get-sync-sem ((train train))
  (slot-value train 'sync-sem))

(defmethod get-passanger-count ((train train))
  (slot-value train 'passanger-count))

(defmethod set-passanger-count ((train train) value)
  (setf (slot-value train 'passanger-count) value))

(defmethod dec-passanger-count ((train train))
  (set-passanger-count train 
                       (- (get-passanger-count train)
                          (get-capacity train))))

(defmethod inc-count ((train train))
  (setf (slot-value train 'count) (+ 1 (slot-value train 'count))))

(defmethod get-count ((train train))
  (slot-value train 'count))

(defmethod set-zero ((train train))
  (setf (slot-value train 'count) 0))

(defmethod dec-count ((train train))
  (setf (slot-value train 'count) (- (slot-value train 'count) 1)))

(defmethod get-capacity ((train train))
  (slot-value train 'capacity))

(defmethod synch-print ((train train) text)
  (sem-wait (get-sync-sem train))
  (print text)
  (sem-signal (get-sync-sem train)))


(defmethod depart ((train train) passanger-count)
  (unless (> passanger-count (get-capacity train))
    (error "Not enought passangers!"))
  (set-load-sem train (make-semaphore (get-capacity train)))
  (sem-signal (get-unload-sem train))
  (sem-wait (get-unload-sem train))
  (set-passanger-count train  passanger-count)
  (dotimes (i passanger-count)
             (a-progn
               (progn
                 (let ((person (make-instance 'person)))
                   (board person train)  
                   (if (check-capacity train)
                       (progn 
                         (run-p train)
                         (unboard person train)
                         (unload-p train))
                     (synch-print train "Not enought passangers")))))))

(defmethod load-p ((train train))
  (print "loading")
  (set-zero train)
  (dotimes (i (get-capacity train))
    (sem-signal (get-load-sem train))))

(defmethod run-p ((train train))
  (sem-wait (get-sync-sem train))
  (inc-count train)
  (if (= (get-count train) (get-capacity train))
      (progn
        (print "departing")
        (sleep 3)
        (sem-signal (get-unload-sem train))))
  (sem-signal (get-sync-sem train)))

(defmethod unload-p ((train train))
  (print "unloading")
  (sem-wait (get-sync-sem train))
  (dec-count train)
  (if (= (get-count train) 1)
      (progn
        (dec-passanger-count train)
        (load-p train))
    (progn
      (sem-signal (get-unload-sem train))))                 
  (sem-signal (get-sync-sem train)))

(defmethod check-capacity ((train train))
  (let ((ok nil))
    (sem-wait (get-sync-sem train))
    (if (<= (get-capacity train) (get-passanger-count train))
        (setf ok t))
    (sem-signal (get-sync-sem train))
    ok))
                                 
  
(defclass person ()
  ())

(defmethod board ((person person) train)
  (sem-wait (get-load-sem train))
  (synch-print train "person enters"))

(defmethod unboard ((person person) train)
  (sem-wait (get-unload-sem train))
  (synch-print train "person leaves"))