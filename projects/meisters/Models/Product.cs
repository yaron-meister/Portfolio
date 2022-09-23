using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public class Product : Observable
    {
        private int _uid;
        private string _name;
        private int _quantity = 1;
        private int _price;

        public Product(int uid, string name, int price = 0)
        {
            Uid = uid;
            Name = name;
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
