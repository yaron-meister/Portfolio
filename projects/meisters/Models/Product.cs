using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public enum EProductType
    {
        Entree,
        Main,
        Extra,
        Dessert,
        Drink,
        Alcohol,
        OTH
    }

    public class Product : Observable
    {
        private int _uid;
        private string _name;
        private int _quantity = 1;
        private EProductType _type;
        private int _price;

        public Product(int uid, string name, EProductType type, int price = 0)
        {
            Uid = uid;
            Name = name;
            Type = type;
            Price = price;
        }

        public int Uid
        {
            get => _uid;
            set
            {
                _uid = value;
                OnPropertyChanged();
            }
        }

        public string Name
        {
            get => _name;
            set
            {
                _name = value;
                OnPropertyChanged();
            }
        }

        public int Quantity
        {
            get => _quantity;
            set
            {
                _quantity = value;
                OnPropertyChanged();
            }
        }

        public EProductType Type
        {
            get => _type;
            set
            {
                _type = value;
                OnPropertyChanged();
            }
        }

        public int Price
        {
            get => _price;
            set
            {
                _price = value;
                OnPropertyChanged();
            }
        }
    }
}
