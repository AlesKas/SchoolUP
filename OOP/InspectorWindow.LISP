#|
Pro správné fungování je potřeba mít načtenou knihovnu micro-graphics a soubor 08.lisp.

Třída inspector-window je potomkem třídy window. Instance představují prohlížeč, který zobrazuje vlastnosti objektu.
Při kliknutí na tvar v okně inspected-window zobrazí jeho vlastnosti. 
Při kliknutí do inspected-window mimo všechny jeho tvary zobrazí vlastnosti inspected-window.
Při dvojkliku na hodnotu vlastnosti zobrazí dialog o změně vlastnosti, po zadání nové hodnoty vlastnost změní.
Pro zobrazování nových vlastností nově definovaných objektů je nutné definovat metodu properties vracející seznam všech 
zobrazovaných vlastností a metodu setable-properties vracející seznam všech nastavitelných vlastností.

       TŘÍDA INSPECTOR-WINDOW

Vlastnosti:
inspected-window: Aktuálně prohlížené okno (instance třídy inspected-window)
inspected-object: Objekt, jehož vlastnosti se zobrazují v instanci třídy ispector-window

Zprávy:
inspected-window: Vrátí aktuálně prohlížené okno (bez parametrů)             
set-inspected-window: Nastaví aktuálně prohlížené okno (1 argument - instance třídy inspected-window)

Upravené zděděné zprávy
ev-mouse-down: Nastaví clicked-object a aktualizuje vypsané informace podle kliknutého objektu   
ev-change: Aktualizuje vypsané informace podle změněného objektu
ev-double-click: Zobrazí formulář pro změnu hodnoty vlastnosti, pokud je zadána, vlastnost změní
                 a aktualizuje vypsané informace podle změněného objektu


       TŘÍDA INSPECTED WINDOW
Třída je potomkem třídy windo a představuje okno určené k prohlížení prohlížečem.

Upravené zděděné zprávy
mouse-down-inside-shape: Při kliknutí na tvar v inspected-window posílá zprávu o kliknutí delegátovi           
mouse-down-no-shape: Při kliknutí do inspected-window mimo všechny jeho tvary posílá 
                     zprávu o kliknutí delegátovi 
ev-change: Při změně objektu uvnitř inspected-window reaguje na změnu 
           a zároveň posílá zprávu delegátovi


      TŘÍDA TEXT SHAPE
Třída je potomkem třídy shape a představuje textové pole.
 
Vlastnosti: 
text: Text, který se zobrazí v objektu
position: Pozice objektu (bod)

      UPRAVENÉ TŘÍDY 

TŘÍDA WINDOW

window-double-click: Zpráva kterou dostane window při dvojkliku         
install-double-click-callback:  Nainstaluje zpětné volání při dvojkliku
install-callbacks: Nainstaluje všechna zpětná volání

TŘÍDA SHAPE

double-click: Zajišťuje posílání zprávy delegátovi tvaru při dvojkliku

TŘÍDA OMG-OBJECT

ev-double-click: Událost, kterou objekt přijímá od objektu, jehož je delegátem při dvojkliku

|#




(defclass inspector-window (window)
  ((inspected-window :initform nil)
   (inspected-object :initform nil)))

(defclass inspected-window (window)
  ())
  
(defmethod inspected-window ((iw inspector-window))
  (slot-value iw 'inspected-window))


(defmethod set-inspected-window ((iw inspector-window) window)
  (unless (typep window 'inspected-window)
    (error "Argument must be a inspected-window"))
  (setf (slot-value iw 'inspected-window) window)
  (set-delegate window iw)
  (set-inspected-object iw window))

(defmethod inspected-object ((iw inspector-window))
  (slot-value iw 'inspected-object))


(defmethod set-inspected-object ((iw inspector-window) object)
  (setf (slot-value iw 'inspected-object) object)
  (set-informations iw object))

(defmethod do-set-informations ((iw inspector-window) window)
  (let ((pic (make-instance 'picture)))
    (set-items pic (make-informations iw window))
    (set-shape iw pic)))    
 
(defmethod set-informations ((iw inspector-window) object)
  (send-with-change iw 
                    'do-set-informations 'set-informations
                    `(,object)))

(defmethod make-row-text ((iw inspector-window) object name y)
  (set-text (move (make-instance 'text-shape) 50 y)
            (format nil "~a : ~a" name (funcall name object))))

(defmethod make-informations ((iw inspector-window) object)
  (let* ((y 35)
         (text (list (set-text (move (make-instance 'text-shape) 50 y)
                               (format nil "CLASS : ~a" (type-of object))))))
    (dolist (name (properties object))
      (setf y (+ y 20))
      (setf text (cons (make-row-text iw object name y)
                       text)))
    text))

(defmethod set-shape-value ((iw inspector-window) text-shape value)
  (let* ((text (text text-shape))
         (slot (subseq text 0 (position #\Space text)))
         (shape (inspected-object iw)))
    (send-with-change shape 
                    (intern (format nil "SET-~a" slot)) 'set-shape-value 
                    `(,value))
      (set-informations iw shape)))
    
(defmethod ev-mouse-down ((iw inspector-window) sender clicked button position)
  (when (eql sender (inspected-window iw))
    (set-inspected-object iw clicked)))

(defmethod ev-change ((iw inspector-window) sender msg orig-obj args)
  (when (eql (inspected-object iw) orig-obj)
    (set-informations iw orig-obj)))

(defmethod ev-double-click ((iw inspector-window) sender clicked button position)
  (let ((list (items (shape iw))))
    (when (and (find clicked (remove (first (last list)) list))
               (check-setable-property iw clicked))
      (let ((value (multiple-value-list
                    (capi:prompt-for-value "Zadejte novou hodnotu"))))
        (when (second value)
          (set-shape-value iw clicked (first value)))))))

(defmethod check-setable-property ((iw inspector-window) clicked)
  (let ((text (subseq (text clicked) 0 (position #\Space (text clicked)))))
    (and (find (intern text) (setable-properties (inspected-object iw)))
         (find-symbol (format nil "SET-~a" text)))))
  
(defmethod mouse-down-inside-shape ((iw inspected-window) shape button position)
  (send-event iw 'ev-mouse-down shape button position)
  iw)

(defmethod mouse-down-no-shape ((iw inspected-window) button position)
  (send-event iw 'ev-mouse-down iw button position)
  iw)

(defmethod ev-change ((iw inspected-window) sender msg orig-obj args)
  (change iw msg orig-obj args)
  (call-next-method))

(defclass text-shape (shape)
  ((text :initform "")
   (position :initform (make-instance 'point))))

(defmethod text ((shape text-shape))
  (slot-value shape 'text))

(defmethod text-position ((shape text-shape))
  (slot-value shape 'position))

(defmethod do-set-text ((shape text-shape) value)
  (setf (slot-value shape 'text) value))

(defmethod set-text ((shape text-shape) value)
  (send-with-change shape
                    'do-set-text 'set-text
                    `(,value)))

(defmethod do-move ((shape text-shape) dx dy)
  (move (text-position shape) dx dy))

(defmethod left ((shape text-shape))
  (+ (first (mg:get-string-extent (shape-mg-window shape)
                                  (text shape)))
     (x (text-position shape))))

(defmethod top ((shape text-shape))
  (+ (second (mg:get-string-extent (shape-mg-window shape)
                                   (text shape)))
     (y (text-position shape))))

(defmethod right ((shape text-shape))
  (+ (third (mg:get-string-extent (shape-mg-window shape)
                                  (text shape)))
     (x (text-position shape))))

(defmethod bottom ((shape text-shape))
  (+ (fourth (mg:get-string-extent (shape-mg-window shape)
                                   (text shape)))
     (y (text-position shape))))


(defmethod contains-point-p ((shape text-shape) point)
  (and (<= (left shape) (x point) (right shape))
       (<= (top shape) (y point) (bottom shape))))

(defmethod do-draw ((shape text-shape)) 
  (mg:draw-string (shape-mg-window shape)
                  (text shape)
                  (x (text-position shape)) 
                  (y (text-position shape))) 
  shape)

;;; úprava třídy window

(defmethod properties((w window))
  '(shape background))

(defmethod setable-properties((w window))
  '(background))

(defmethod window-double-click ((w window) button position)
  (let ((shape (find-clicked-shape w position)))
    (when shape 
        (double-click shape button position))))

(defmethod install-double-click-callback ((w window))
  (mg:set-callback 
   (mg-window w) 
   :double-click (lambda (mgw button x y)
		 (declare (ignore mgw))
		 (window-double-click
                  w
                  button 
                  (move (make-instance 'point) x y)))))

(defmethod install-callbacks :after ((w window))
  (install-display-callback w)
  (install-mouse-down-callback w)
  (install-double-click-callback w)
  w)

;;;úpravy stávajících tříd 

(defmethod properties((s shape))
  '(color thickness filledp))

(defmethod setable-properties((s shape))
  '(color thickness filledp))
  
(defmethod double-click ((shape shape) button position)
  (send-event shape 'ev-double-click shape button position))

;;;omg-object

(defmethod ev-double-click 
           ((obj omg-object) sender clicked button position)
  (send-event obj 'ev-double-click clicked button position))

;;;compound-shape

(defmethod properties((cs compound-shape))
  (append (call-next-method)
          '(items)))

;;;polygon

(defmethod properties((p polygon))
  (append (call-next-method)
          '(closedp)))

(defmethod setable-properties((p polygon))
  (append (call-next-method)
          '(closedp)))
 
;;;circle

(defmethod properties((c circle))
  (append (call-next-method)
          '(center radius)))

(defmethod setable-properties((c circle))
  (append (call-next-method)
          '(center radius)))

;;;point

(defmethod properties((p point))
  (append (call-next-method)
          '(x y r phi)))

(defmethod setable-properties((p point))
  (append (call-next-method)
          '(x y r phi)))

#|
(setf w (make-instance 'inspected-window))
(setf iw (make-instance 'inspector-window))
(set-inspected-window iw w)
|#