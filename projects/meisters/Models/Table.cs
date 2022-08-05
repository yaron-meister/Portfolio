using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public enum ETableStatus
    {
        Clear,
        NoOrder,
        Order,
        Check
    }

    class Table : Observable
    {
        private ETableStatus _status = ETableStatus.Clear;

        public Table(int id)
        {
            ID = id;
        }

        public int ID { get; }

        public ETableStatus Status
        {
            get => _status;
            set
            {
                _status = value;
                OnPropertyChanged();
            }
        }
    }
}
