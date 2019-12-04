<h1><?=$nadpis;?></h1>
<aside>
        <br/>
        <br/>
        <h2>Architektura MVC</h2>
          <p>
            <b>Model-view-controller</b> je softwarová architektura, která rozděluje datový model aplikace, uživatelské rozhraní a řídící logiku.<br/>
            <ul>
                <li>Model - datová struktura</li>
                <li>View - převádí data repzentovaná model do uživatelského rozhraní.</li>
                <li>Controller - reaguje na události, a zajišťuje změny v modelu nebo pohledu</li>
            </ul>
          </p>
        <h2>Singleton</h2>
          <p>Singleton je návrhový formát, při kterém v celou dobu běhu programu běží jenom jedna instance třídy.</p>
        <h2>Modifikátory přístupu</h2>
          <p>Modifikátory přístupu jsou klíčová slova sloužící k určení deklarovaného přístupnosti člena nebo typu. Modifikátory jsou následující: <br/>
            <ul>
              <li>Public - Přístup není omezen</li>
              <li>Protected - Přístup omezen na na třídu, ve které je obsažen, nebo na třídu, která z této třídy dědí</li>
              <li>Private - Přístup omezen pouze na třídu, ve které je obsažen</li>
            </ul>
          </p>
        <h2>Namespace</h2>
          <p>
            Jmenné prostory slouží k tomu, aby logicky sdružovaly typy, které spolu souvisejí. <br/>
            Příkladem může být namespace <b>System</b> používaný v jazyce C#, který definuje běžně používané hodnoty
             a referenční datové typy, události a obslužné rutiny událostí, rozhraní, atributy a zpracování výjimek.
          </p>
        <h2>Magické metody</h2>
        <p>Magické metody se nazývají magické proto, že je nevoláme sami, ale spouští se v určitých chvílích automaciky, např. při reakci na události.
          Některé magické metody jsou: <br/>
          <ul>
            <li>Konstruktor - vytváří instanci třídy, v PHP metoda <b>__construct</b></li>
            <li>Destruktor - metoda, která je volána, když se daný objekt odstraňjuje z paměti. V PHP metoda <b>__destruct</b></li>
            <li>ToString - metoda, která je volána, když daný objekt chceme převést na textový řetězec. V PHP metoda <b>__toString</b></li>
          </ul>
        </p>
      </aside>