using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using DOVY.Models;

namespace DOVY
{
    /// <summary>
    /// Interaction logic for Detail.xaml
    /// </summary>
    public partial class Detail : Window
    {
        public Detail(Entities ctx, Meal jidlo)
        {
            InitializeComponent();
            var list = new List<DetailClass>();
            foreach(var ingredient in jidlo.MealConsistsOfs)
            {
                var ing = new DetailClass
                {
                    Amount = (double)ingredient.AmountRequired,
                    Name = ingredient.Ingredient.Name,
                    UnitOfMeasure = ingredient.Ingredient.UnitOfMeasure
                };
                list.Add(ing);
            }
            IngredientsDataGrid.DataContext = list;
        }
    }

    class DetailClass
    {
        public DetailClass(){
        }
        public double Amount { get; set; }
        public string UnitOfMeasure { get; set; }
        public string Name { get; set; }
    }
}
