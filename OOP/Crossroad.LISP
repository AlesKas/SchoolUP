#|
Dokumentace
OOP 2. úkol - křižovatka
Pro správné fungování je potřeba načíst knihovnu Micro-graphics a soubory 06.lisp a 05_light.lisp

Třída Semaphore je potomkem třídy picture, a její isntance představují semafor, jehož světla svítí v závislosti na tom, v jaké je semafor fázi. Změna fáze se provádí zprávou set-semaphore-phase pro nastavení určité fáze, nebo zprávou next-phase pro přechod do další fáze. Typ semaforu se dělí na dva základní, a to :pedestrian a :vehicle.
Vlastnosti:

lights - seznam světel semaforu
box - "krabice" semaforu
semaphore-phase - aktuální fáze
semaphore-type - typ semaforu

Zprávy:

next-phase - přepne semafor na další fázi
set-semaphore-type - změní typ semaforu
set-semaphore-phase - změní fázi semaforu na zadané číslo

Třída Crossroads
Třída crossroads je potomkem třídy picture, její instance představuje přednastavený obrázek křizovatky využívající několika instancí třídy semaphore a volaním zprávy next-phase vidíme, jak by taková jednoduchá křizovatka mohla fungovat

Zprávy:

next-phase - přepne křižovatku na další fázi
set-crossroads-phase - změní fázi křižovatky na zadané číslo
set-program - nastaví program křižovatky na seznam seznamů obsahující fáze jednotlivých semaforů

|#

(defvar *semaphore-size* 20 )
;;sirka semaforu a zaroven vyska jednotlivych svetel
(defvar *light-part* 3/4)
;;podil svetla na misto v semaforu

(defvar *semaphore-types*
  '((:pedestrian (:red :green) ((t nil) (nil t)))
    (:vehicle (:red :orange :green) ((t nil nil) (t t nil) (nil nil t) (nil t nil)))
    (:pedo (:red :green :green :green) ((t nil t nil) (nil t nil t) (t t t t) (t t t t)))))
;;typy semaforu a jejich faze

(defun semaphore-description (type)
  (assoc type *semaphore-types*))

(defun semaphore-colors (type)
  (second (semaphore-description type)))

(defun semaphore-phase-descriptions (type)
  (third (semaphore-description type)))

(defun semaphore-phase-description (type phase)
  (let ((phases (semaphore-phase-descriptions type)))
    (nth (mod phase (length phases)) phases)))

(defclass semaphore (picture)
  ((lights :initform (make-instance 'picture))
   (box :initform (set-filledp (make-instance 'polygon) t))
   (semaphore-phase :initform 0)
   (semaphore-type :initform :vehicle)))

(defmethod semaphore-phase-count ((sem semaphore))
  (length (third (assoc (semaphore-type sem) *semaphore-types*))))

(defun make-light (position color)
  (move
   (set-radius 
    (set-on-color (make-instance 'light) color)
    (* 1/2 *light-part* *semaphore-size*))
   (* 1/2 *semaphore-size*)
   (+ (* 1/2 *semaphore-size*)
      (* position *semaphore-size*))))

(defun make-light-list (count type)
  (let ((colors (semaphore-colors type))
        result)
    (dotimes (i count)
      (setf result (cons (make-light i (nth i colors)) result)))
    (reverse result)))
 
(defun make-box-points (count)
  (list (make-instance 'point)
        (move (make-instance 'point) *semaphore-size* 0)
        (move (make-instance 'point)
              *semaphore-size*
              (* count *semaphore-size*))
        (move (make-instance 'point) 0 (* count *semaphore-size*))))

(defmethod light-count ((sem semaphore))
  (length (items (slot-value sem 'lights))))

(defmethod set-light-count ((sem semaphore) count)
  (set-items (slot-value sem 'lights)
             (make-light-list count (slot-value sem 'semaphore-type)))
  (set-items (slot-value sem 'box)
             (make-box-points count))
  (set-semaphore-phase sem 0)
  sem)

(defun set-light-phase (lights phase)
  (dolist (pair (mapcar #'cons lights phase))
    (set-onp (car pair) (cdr pair))))
  
(defmethod semaphore-phase ((sem semaphore))
  (slot-value sem 'semaphore-phase))

(defmethod semaphore-type ((sem semaphore))
  (slot-value sem 'semaphore-type))

(defmethod set-semaphore-type ((Sem semaphore) type)
      (setf (slot-value sem 'semaphore-type) type)
      (set-light-count sem 
                   (length (semaphore-colors 
                            (slot-value sem 'semaphore-type)))))


(defmethod set-semaphore-phase ((sem semaphore) phase-no)
  (set-light-phase (items (slot-value sem 'lights))
                   (semaphore-phase-description (slot-value sem 'semaphore-type) phase-no))
  (setf (slot-value sem 'semaphore-phase) phase-no)
  sem)

(defmethod next-phase ((sem semaphore))
  (set-semaphore-phase sem (+ (semaphore-phase sem) 1)))

(defmethod initialize-instance ((sem semaphore) &key)
  (call-next-method)
  (set-items sem (list (slot-value sem 'lights)
                       (slot-value sem 'box)))
  (set-light-count sem 
                   (length (semaphore-colors 
                            (slot-value sem 'semaphore-type)))))

(defclass crossroads (picture)
  ((semaphores :initform '())
   (program :initform '())
   (crossroads-phase :initform 0)))

(defmethod crossroads-phase-count ((cr crossroads))
  (length (slot-value cr 'program)))

(defmethod semaphores ((cr crossroads))
 (reverse (contains-semaphores cr cr)))

(defmethod contains-semaphores ((cr crossroads) picture)
  (let ((semaphores '()))
    (dolist (item (items picture))
      (cond ((typep item 'semaphore)
             (setf semaphores (cons item semaphores)))
            ((typep item 'picture)
             (setf semaphores (append (contains-semaphores cr item) semaphores)))))
    semaphores))

(defmethod phase-count ((cr crossroads))
  (list-length (slot-value cr 'program)))

(defmethod next-phase ((c crossroads))
  (let ((phase (+ (crossroads-phase c) 1))
        (count (phase-count c)))
    (set-crossroads-phase c (mod phase count))))

(defmethod set-crossroads-phase ((c crossroads) value) 
  (unless (typep value 'number)
    (error "Value must be a number"))
  (unless (< value (phase-count c))
    (error "Invalid phase of semaphore."))
  (setf (slot-value c 'crossroads-phase) value)
  (set-semaphores-phases c value))
             
(defmethod set-semaphores-phases ((c crossroads) value)
  (let ((phase (nth value (program c)))
        (semaphores (semaphores c)))
     (dotimes (index (list-length semaphores) c)
                  (set-semaphore-phase (nth index semaphores )
                                       (nth index phase)))))

(defmethod set-program ((cr crossroads) program)
  (setf (slot-value cr 'program) program)
  (next-phase cr))

(defmethod program ((cr crossroads))
  (slot-value cr 'program))

(defmethod crossroads-phase ((cr crossroads))
  (slot-value cr 'crossroads-phase))

#|
(setf cr (make-instance 'crossroads))
(next-phase cr)
|#