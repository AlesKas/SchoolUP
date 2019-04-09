using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;
using System.Xml.Serialization;

namespace HW9
{
    /// <summary>
    /// Interakční logika pro MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            List<ordered_setElement> elements = loadElems();
            List<ordered_setOrder> order = loadOrder();
            draw(elements, order);
        }

        private void draw(List<ordered_setElement> elements, List<ordered_setOrder> order)
        {

            foreach(ordered_setElement el in elements)
            {
                Ellipse e = new Ellipse();
                e.Stroke = Brushes.Black;
                e.Fill = Brushes.Black;
                e.Width = 10;
                e.Height = 10;
                e.Cursor = Cursors.Hand;
                canvas.Children.Add(e);
                Canvas.SetLeft(e, el.x);
                Canvas.SetTop(e, el.y);
                e.MouseDown += delegate (object sender, MouseButtonEventArgs ev)
                {
                    TextBlock tx = new TextBlock();
                    tx.Text = "{" + el.objects.ToString() + "}, {" + el.attributes.ToString() + "}";
                    Canvas.SetLeft(tx, el.x);
                    Canvas.SetTop(tx, el.y);
                    canvas.Children.Add(tx);
                };
            }
            foreach(ordered_setOrder or in order)
            {
                Line l = new Line();
                l.Stroke = Brushes.Red;
                l.Fill = Brushes.Red;
                l.StrokeThickness = 2;
                l.X1 = elements[or.smaller-1].x +5;
                l.X2 = elements[or.bigger-1].x+5;
                l.Y1 = elements[or.smaller-1].y+5;
                l.Y2 = elements[or.bigger-1].y+5;
                canvas.Children.Add(l);
            }
        }

        private List<ordered_setElement> loadElems()
        {
            List<ordered_setElement> set = new List<ordered_setElement>();
            try
            {
                FileStream f = new FileStream(@"C:\Users\Aleš\Documents\GitHub\SchoolDesktop\C#\HW9\load.xml", FileMode.Open);
                XmlSerializer serializer = new XmlSerializer(typeof(ordered_set));
                ordered_set s = (ordered_set)serializer.Deserialize(f);
                foreach(ordered_setElement el in s.elements)
                {
                    set.Add(el);
                }
                f.Close();
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message);
            }
            return set;
        }
        private List<ordered_setOrder> loadOrder()
        {
            List<ordered_setOrder> order = new List<ordered_setOrder>();
            try
            {
                FileStream f = new FileStream(@"C:\Users\Aleš\Documents\GitHub\SchoolDesktop\C#\HW9\load.xml", FileMode.Open);
                XmlSerializer serializer = new XmlSerializer(typeof(ordered_set));
                ordered_set s = (ordered_set)serializer.Deserialize(f);
                foreach (ordered_setOrder ord in s.orders)
                {
                    order.Add(ord);
                }
                f.Close();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }           
            return order;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SaveFileDialog save = new SaveFileDialog();
                if(save.ShowDialog() == true)
                {
                    RenderTargetBitmap rtb = new RenderTargetBitmap((int)canvas.RenderSize.Width, (int)canvas.RenderSize.Height, 96, 96, PixelFormats.Default);
                    rtb.Render(canvas);
                    BitmapEncoder encoder = new PngBitmapEncoder();
                    encoder.Frames.Add(BitmapFrame.Create(rtb));
                    using (var fs = File.OpenWrite(save.FileName))
                    {
                        encoder.Save(fs);
                    }
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }


    // POZNÁMKA: Generovaný kód může vyžadovat alespoň rozhraní .NET Framework 4.5 nebo .NET Core/Standard 2.0.
    /// <remarks/>
    [System.SerializableAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true)]
    [System.Xml.Serialization.XmlRootAttribute(Namespace = "", IsNullable = false)]
    public partial class ordered_set
    {

        private ordered_setElement[] elementsField;

        private ordered_setOrder[] ordersField;

        /// <remarks/>
        [System.Xml.Serialization.XmlArrayItemAttribute("element", IsNullable = false)]
        public ordered_setElement[] elements
        {
            get
            {
                return this.elementsField;
            }
            set
            {
                this.elementsField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlArrayItemAttribute("order", IsNullable = false)]
        public ordered_setOrder[] orders
        {
            get
            {
                return this.ordersField;
            }
            set
            {
                this.ordersField = value;
            }
        }
    }

    /// <remarks/>
    [System.SerializableAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true)]
    public partial class ordered_setElement
    {

        private ushort xField;

        private ushort yField;

        private string objectsField;

        private string attributesField;

        private byte idField;

        /// <remarks/>
        public ushort x
        {
            get
            {
                return this.xField;
            }
            set
            {
                this.xField = value;
            }
        }

        /// <remarks/>
        public ushort y
        {
            get
            {
                return this.yField;
            }
            set
            {
                this.yField = value;
            }
        }

        /// <remarks/>
        public string objects
        {
            get
            {
                return this.objectsField;
            }
            set
            {
                this.objectsField = value;
            }
        }

        /// <remarks/>
        public string attributes
        {
            get
            {
                return this.attributesField;
            }
            set
            {
                this.attributesField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public byte id
        {
            get
            {
                return this.idField;
            }
            set
            {
                this.idField = value;
            }
        }
    }

    /// <remarks/>
    [System.SerializableAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true)]
    public partial class ordered_setOrder
    {

        private byte biggerField;

        private byte smallerField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public byte bigger
        {
            get
            {
                return this.biggerField;
            }
            set
            {
                this.biggerField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public byte smaller
        {
            get
            {
                return this.smallerField;
            }
            set
            {
                this.smallerField = value;
            }
        }
    }


}
